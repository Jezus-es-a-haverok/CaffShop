from django.db import models
from django.conf import settings
import uuid  # Required for unique CAFF file instances



class Comment(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, help_text='Unique ID of the comment')
    image = models.ForeignKey('CAFF', on_delete=models.SET_NULL, null=True, related_name='comments')
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.SET_NULL, null=True)
    text = models.TextField(max_length=1000, help_text='Comment text')
    date = models.DateField(auto_now_add=True)
    active = models.BooleanField(default=True)


    class Meta:
        ordering = ['date', 'id']

    def __str__(self):
        """String for representing the Model object."""
        return 'Comment {} at {}'.format(self.text, self.image.name)

class CAFF(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, help_text='Unique ID of the CAFF file')
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.SET_NULL, null=True)
    creator = models.CharField(max_length=200, help_text='Name of the creator')
    creation_date = models.DateField(null=True, blank=True)  # TODO default érték a mostani
    upload_date = models.DateField(null=True, blank=True)  # TODO default érték a mostani
    name = models.CharField(max_length=200, help_text='Name of the CAFF file')
    content = models.FileField(null=False, blank=False, upload_to="images")
    thumbnail = models.FileField(null=False, blank=False, upload_to="images")
    captions = models.JSONField(null=True, blank=True, help_text='Captions for the CAFF file')  # kicsit fura, hogy több caption
    tags = models.JSONField(null=True, blank=True, help_text='Tags of the CAFF file')

    class Meta:
        ordering = ['upload_date']

    def __str__(self):
        """String for representing the Model object."""
        return f'{self.creator}:  {self.name}'
