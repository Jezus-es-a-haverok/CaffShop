from django.utils import timezone
from django.views.generic.list import ListView
from .filters import CAFFFilter
from .models import CAFF

class CAFFListView(ListView):

    model = CAFF
    paginate_by = 100  # if pagination is desired

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['filter'] = CAFFFilter(self.request.GET, queryset=self.get_queryset())
        return context