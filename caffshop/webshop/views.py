from django.utils import timezone
from django.views.generic.list import ListView
from django.views.generic.detail import DetailView
from .filters import CAFFFilter
from .models import CAFF
from .models import Comment
from django.http import HttpResponseRedirect
from django.http import FileResponse
from django.shortcuts import render, get_object_or_404
from .forms import UploadCAFFForm
from .forms import CommentForm
import datetime
from PIL import Image
from django.core.files import File as DjangoFile
import numpy as np
import sys
import io
sys.path.append("../lib")
import libcaffparser

class CAFFListView(ListView):

    model = CAFF
    paginate_by = 100  # if pagination is desired

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['filter'] = CAFFFilter(self.request.GET, queryset=self.get_queryset())
        return context

def upload_caff(request):
    if request.method == 'POST':
        form = UploadCAFFForm(request.POST, request.FILES)
        if form.is_valid():
            content = form.cleaned_data['content'].read()
            caff = libcaffparser.parse(content, len(content))
            if caff.getCode() == libcaffparser.OK:

                # Convert to image
                array = np.array(caff.getThumbnail()[0:caff.getWidth() * caff.getHeight()*3], dtype=np.uint8)
                B = np.reshape(array,(caff.getHeight(), caff.getWidth(), 3))
                thumbnailImage = Image.fromarray(B, 'RGB')

                # Save into buffer
                buf = io.BytesIO()
                thumbnailImage.save(buf, format='PNG')
                byte_im = buf.getvalue()

                # Save to file with django
                file_obj1 = DjangoFile(open("thumbnailImage.png", mode='wb+'), name=str(form.cleaned_data['name']))
                file_obj1.write(byte_im)

                # Create CAFF object
                record = CAFF()
                record.content = request.FILES['content']
                record.name = form.cleaned_data['name']
                record.thumbnail = file_obj1
                record.user = request.user
                record.creator = caff.getCreator()
                record.creation_date = datetime.datetime(
                    year = caff.getYear(),
                    month = caff.getMonth(),
                    day = caff.getDay(),
                    hour = caff.getHour(),
                    minute = caff.getMin(),
                    )
                record.upload_date = datetime.datetime.now()
                record.tags = caff.getTags()
                record.captions = caff.getCaptions()
                record.save()

    else:
        form = UploadCAFFForm()
    return render(request, 'webshop/upload.html', {'form': form})


def caff_detailview(request, id):

    template_name = 'webshop/caff_detailView.html'
    caff = get_object_or_404(CAFF, id=id)
    print(caff.content)
    comments = caff.comments.filter(active=True)
    new_comment = None

    # Comment posted
    if request.method == 'POST':
        comment_form = CommentForm(data=request.POST)
        if comment_form.is_valid():
            # Create Comment object but don't save to database yet
            new_comment = comment_form.save(commit=False)
            # Assign the current post to the comment
            new_comment.image = caff
            new_comment.user = request.user
            # Save the comment to the database
            new_comment.save()
    else:
        comment_form = CommentForm()

    return render(request, template_name, {'caff': caff,
                                           'comments': comments,
                                           'new_comment': new_comment,
                                           'comment_form': comment_form})


def caff_download(request, id):
    template_name = 'webshop/caff_detailView.html'
    caff = get_object_or_404(CAFF, id=id)
    response = FileResponse(open("media/" + str(caff.content), 'rb'))

    return response