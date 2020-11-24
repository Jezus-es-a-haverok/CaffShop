from django.utils import timezone
from django.views.generic.list import ListView
from .filters import CAFFFilter
from .models import CAFF
from django.http import HttpResponseRedirect
from django.shortcuts import render
from .forms import UploadCAFFForm

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
            form.save()
    else:
        form = UploadCAFFForm()
    return render(request, 'webshop/upload.html', {'form': form})