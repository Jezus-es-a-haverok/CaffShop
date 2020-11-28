from django.urls import path
from .views import CAFFDetailView
from . import views

urlpatterns = [
    path('<slug>/', views.CAFFDetailView, name='detailView'),
]
