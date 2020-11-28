from django.urls import path
from .views import caff_detailview

from . import views

urlpatterns = [
    path('', views.CAFFListView.as_view()),
    path('upload/', views.upload_caff, name='caff-upload'),
    path('<id>/', views.caff_detailview, name='caff_detailView')
]