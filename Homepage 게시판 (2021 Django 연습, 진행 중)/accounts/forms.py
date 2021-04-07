from django import forms
from .models import Chat
from imagekit.forms import ProcessedImageField

from django.contrib.auth.forms import UserChangeForm, UserCreationForm
from django.contrib.auth import get_user_model

class CustomUserChangeForm(UserChangeForm):
    introduction = forms.CharField(
        label='자기소개 (500자 이내)',
        widget=forms.TextInput(
            attrs={
                'class': '',
                'placeholder': '자기 소개를 해주세요.',
            }
        )
    )

    class Meta:
        model = get_user_model()
        fields = ('introduction', 'profile_image', 'first_name', 'last_name', 'email',)


class CustomUserCreationForm(UserCreationForm):
    class Meta(UserCreationForm.Meta):
        model = get_user_model()
        fields = UserCreationForm.Meta.fields


class ChatFrom(forms.ModelForm):
    message = forms.CharField(
        label='',
        widget=forms.TextInput(
            attrs={
                'class': '',
                'placeholder': 'message'
            }
        )
    )
    class Meta:
        model = Chat
        fields = ('message',)