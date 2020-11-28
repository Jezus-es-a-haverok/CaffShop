from django.forms import ModelForm
from .models import CAFF
from .models import Comment


# class UploadCAFFForm(ModelForm):
#     class Meta:
#         model = CAFF
#         fields = ['name', 'content']


class CommentForm(ModelForm):
    class Meta:
        model = Comment
        fields = ('text',)