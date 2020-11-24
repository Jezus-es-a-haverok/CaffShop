from django.forms import ModelForm
from .models import CAFF

class UploadCAFFForm(ModelForm):
    class Meta:
        model = CAFF
        fields = ['name', 'content']
