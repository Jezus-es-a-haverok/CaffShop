from django.urls import path

from . import views

urlpatterns = [
    path('', views.CAFFListView.as_view(), name='webshop'),
    path('upload/', views.upload_caff, name='caff-upload'),
]
