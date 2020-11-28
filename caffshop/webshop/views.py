from django.shortcuts import render, get_object_or_404
from django.views.generic.detail import DetailView
from .forms import CommentForm
# Create your views here.

from .models import CAFF
from .models import Caption
from .models import Tag
from .models import Comment


# class CAFFDetailView(DetailView):
#     model = CAFF
#     # model = Tag
#     # model = Comment
#     # model = Caption
#
#     template_name = 'webshop/detailView.html'
#     caff = get_object_or_404(CAFF, slug=slug)
#
#     context_object_name = 'caff'


def CAFFDetailView(request, slug):
    template_name = 'webshop/detailView.html'
    caff = get_object_or_404(CAFF, slug=slug)
    comments = caff.comments.filter(active=True)
    new_comment = None
    # Comment posted
    if request.method == 'POST':
        comment_form = CommentForm(data=request.POST)
        if comment_form.is_valid():
            # Create Comment object but don't save to database yet
            new_comment = comment_form.save(commit=False)
            # Assign the current post to the comment
            new_comment.caff = caff
            # Save the comment to the database
            new_comment.save()
    else:
        comment_form = CommentForm()

    return render(request, template_name, {'caff': caff,
                                           'comments': comments,
                                           'new_comment': new_comment,
                                           'comment_form': comment_form})



# def caff_detail(request, slug):
#     template_name = 'webshop/comment.html'
#     caff = get_object_or_404(CAFF, slug=slug)
#     comments = caff.comments.filter(active=True)
#     new_comment = None
#     # Comment posted
#     if request.method == 'POST':
#         comment_form = CommentForm(data=request.POST)
#         if comment_form.is_valid():
#             # Create Comment object but don't save to database yet
#             new_comment = comment_form.save(commit=False)
#             # Assign the current post to the comment
#             new_comment.caff = caff
#             # Save the comment to the database
#             new_comment.save()
#     else:
#         comment_form = CommentForm()
#
#     return render(request, template_name, {'caff': caff,
#                                            'comments': comments,
#                                            'new_comment': new_comment,
#                                            'comment_form': comment_form})

