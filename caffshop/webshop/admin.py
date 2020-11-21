from django.contrib import admin
from .models import Tag, Caption, Comment, CAFF

admin.site.register(Tag)
admin.site.register(Caption)
admin.site.register(Comment)
admin.site.register(CAFF)
