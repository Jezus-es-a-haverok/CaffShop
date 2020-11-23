from django.urls import path

from webshop.views import CAFFListView

urlpatterns = [
    path('', CAFFListView.as_view(), name='caff-list'),
]