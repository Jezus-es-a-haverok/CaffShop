from django.db import models
from django.conf import settings
import uuid  # Required for unique book instances



class Comment(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, help_text='Unique ID for this particular book across whole library')
    image = models.ForeignKey('CAFF', on_delete=models.SET_NULL, null=True)
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.SET_NULL, null=True)
    text = models.TextField(max_length=1000, help_text='Enter your comment')
    date = models.DateField(null=True, blank=True)  #TODO default érték a mostani

    class Meta:
        ordering = ['date', 'id']

    def __str__(self):
        """String for representing the Model object."""
        return f'{self.text}'

class Caption(models.Model):
    name = models.CharField(max_length=200, help_text='Enter a caption')

    def __str__(self):
        return self.name

class Tag(models.Model):
    name = models.CharField(max_length=200, help_text='Enter a caption')

    def __str__(self):
        return self.name

class CAFF(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, help_text='Unique ID for this particular book across whole library')
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.SET_NULL, null=True)
    creator = models.CharField(max_length=200, help_text='Enter the name of the creator')
    creation_date = models.DateField(null=True, blank=True)  # TODO default érték a mostani
    upload_date = models.DateField(null=True, blank=True)  # TODO default érték a mostani
    name = models.CharField(max_length=200, help_text='Enter a caption')
    content = models.BinaryField()
    thumbnail = models.BinaryField()
    captions = models.ManyToManyField(Caption, help_text='Captions for the CAFF')  # kicsit fura, hogy több caption
    tags = models.ManyToManyField(Tag, help_text='Tags for the CAFF')

    class Meta:
        ordering = ['upload_date']

    def __str__(self):
        """String for representing the Model object."""
        return f'{self.creator}:  {self.name}'
