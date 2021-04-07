from django.urls import path
from . import views

app_name = 'community'
urlpatterns = [
    path('', views.index, name='index'),
    path('create/', views.create, name='create'),
    path('<int:article_id>/', views.detail, name='detail'),
    path('<int:article_id>/comment/', views.create_comment, name='create_comment'),
    path('<int:article_id>/comment/<int:comment_id>/delete/', views.delete_comment, name='delete_comment'),
    path('<int:article_id>/update/', views.update, name='update'),
    path('<int:article_id>/delete/', views.delete, name='delete'),
    path('<int:article_id>/like/', views.like, name='like'),
]