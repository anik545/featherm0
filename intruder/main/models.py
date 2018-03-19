from django.db import models

# Create your models here.
class Motion(models.Model):
    new_state = models.BooleanField()
    time = models.DateTimeField()