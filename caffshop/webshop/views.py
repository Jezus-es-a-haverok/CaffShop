from django.utils import timezone
from django.views.generic.list import ListView
from .filters import CAFFFilter
from .models import CAFF
from django.http import HttpResponseRedirect
from django.shortcuts import render
from .forms import UploadCAFFForm
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
