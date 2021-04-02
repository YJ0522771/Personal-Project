from django.db import models
from django.contrib.auth.models import AbstractUser
from django.conf import settings

from imagekit.models import ProcessedImageField
from imagekit.processors import Thumbnail

class User(AbstractUser):
    # 프로필 이미지
    profile_image = ProcessedImageField(
        blank=True,
        upload_to='images/user_profiles/',
        processors=[Thumbnail(100, 100)],
        format='JPEG',
        options={
            'quality': 80,
        }
    )
    # 자기 소개
    introduction = models.CharField(max_length=500)
    # 가입일
    signedup_at = models.DateTimeField(auto_now_add=True)

    followings = models.ManyToManyField('self', symmetrical=False, related_name='followers')
    chat_users = models.ManyToManyField('self', through='Chat')


class Chat(models.Model):
    user = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.CASCADE)
    message = models.CharField(max_length=100)
    time = models.DateTimeField(auto_now_add=True)

