from django import forms

class UploadCAFFForm(forms.Form):
    name = forms.CharField(max_length=50)
    content = forms.ImageField()