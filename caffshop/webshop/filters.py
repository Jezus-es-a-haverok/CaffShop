import django_filters
from .models import CAFF

class CAFFFilter(django_filters.FilterSet):
    class Meta:
        model = CAFF
        fields = {
            'creator': ['icontains'],
            'name': ['icontains'],
        }
