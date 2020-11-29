from django.urls import path
from django.contrib.auth.decorators import login_required
from . import views

urlpatterns = [
    path('', login_required(views.CAFFListView.as_view()), name='webshop'),
    path('upload/', views.upload_caff, name='caff-upload'),
    path('<id>/', views.caff_detailview, name='caff_detailView'),
    path('download/<id>/', views.caff_download, name='caff_download')
]
