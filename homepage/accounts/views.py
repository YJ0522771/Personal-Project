from django.shortcuts import render,redirect, get_object_or_404


from django.contrib.auth.forms import AuthenticationForm, PasswordChangeForm
from .forms import CustomUserChangeForm, CustomUserCreationForm
from django.contrib.auth import login as auth_login
from django.contrib.auth import logout as auth_logout
from django.contrib.auth import update_session_auth_hash
from django.contrib.auth import get_user_model


def signup(request):
    if request.user.is_authenticated:
        return redirect('community:index')
    
    if request.method == 'POST':
        form = CustomUserCreationForm(request.POST)
        if form.is_valid():
            user = form.save()
            auth_login(request, user)
            return redirect('community:index')
    else:
        form = CustomUserCreationForm()
    context = {
        'form': form,
    }
    return render(request, 'accounts/signup.html', context)


def login(request):
    if request.user.is_authenticated:
        return redirect('community:index')
    
    if request.method == 'POST':
        form = AuthenticationForm(request, request.POST)
        if form.is_valid():
            # 주의
            auth_login(request, form.get_user())
            return redirect('community:index')
    else:
        form = AuthenticationForm()
    context = {
        'form': form,
    }
    return render(request, 'accounts/login.html', context)


def logout(request):
    if not request.user.is_authenticated:
        return redirect('community:index')
    if request.method == 'POST':
        auth_logout(request)
    return redirect('community:index')


def profile(request, username):
    user_info = get_object_or_404(get_user_model(), username=username)
    if not user_info.profile_image:
        profile_path = '/static/accounts/img/default.jpg'
    else:
        profile_path = user_info.profile_image
    followers_count = user_info.followers.all().count()
    followings_count = user_info.followings.all().count()
    if request.user.is_authenticated:
        is_following = user_info.followers.filter(pk=request.user.pk).exists()
    else:
        is_following = False
    context = {
        'user_info': user_info,
        'profile_path': profile_path,
        'followers_count': followers_count,
        'followings_count': followings_count,
        'is_following': is_following,
    }
    return render(request, 'accounts/userinfo.html', context)


def update(request):
    if not request.user.is_authenticated:
        return redirect('community:index')
    
    if request.method == 'POST':
        form = CustomUserChangeForm(request.POST, instance=request.user)
        if form.is_valid():
            form.save()
            return redirect('accounts:profile', request.user.username)
    else:
        form = CustomUserChangeForm(instance=request.user)
    context = {
        'form': form,
    }
    return render(request, 'accounts/update.html', context)


def update_password(request):
    if not request.user.is_authenticated:
        return redirect('community:index')
    
    if request.method == 'POST':
        form = PasswordChangeForm(request.user, request.POST)
        if form.is_valid():
            user = form.save()
            update_session_auth_hash(request, user)
            return redirect('accounts:update')
    else:
        form = PasswordChangeForm(request.user)
    context = {
        'form': form,
    }
    return render(request, 'accounts/password.html', context)


def delete(request):
    if not request.user.is_authenticated:
        return redirect('community:index')

    if request.method == 'POST':
        # 순서 유의
        request.user.delete()
        auth_logout(request)
    return redirect('community:index')


def follow(request, username):
    if not request.user.is_authenticated:
        return redirect('accounts:profile', username)

    if request.method == 'POST':
        user = get_object_or_404(get_user_model(), username=username)
        if user.followers.filter(pk=request.user.pk).exists():
            user.followers.remove(request.user)
        else:
            user.followers.add(request.user)
    return redirect('accounts:profile', username)