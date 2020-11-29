from django.urls import path

from . import views

urlpatterns = [
    path('', views.CAFFListView.as_view(), name='webshop'),
    path('upload/', views.upload_caff, name='caff-upload'),
    path('<id>/', views.caff_detailview, name='caff_detailView'),
    path('download/<id>/', views.caff_download, name='caff_download')
]
