from django.shortcuts import render, redirect, get_object_or_404
from .models import Article, Comment
from .forms import ArticleForm, CommentForm

# Create your views here.
def index(request):
    articles = Article.objects.order_by('-pk')
    article_dicts = []
    for article in articles:
        d = {}
        d['pk'] = article.pk
        d['article'] = article
        d['like'] = article.like_users.all().count()
        article_dicts.append(d)
    context = {
        'article_dicts': article_dicts,
    }
    return render(request, 'community/index.html', context)


def create(request):
    if not request.user.is_authenticated:
        return redirect('accounts:login')

    if request.method == 'POST':
        form = ArticleForm(request.POST)
        if form.is_valid():
            article = form.save(commit=False)
            article.user = request.user
            article.save()
            return redirect('community:detail', article.id)
    else:
        form = ArticleForm()
    context = {
        'form': form,
    }
    return render(request, 'community/create.html', context)


def detail(request, article_id):
    article = get_object_or_404(Article, pk=article_id)
    if request.user.is_authenticated:
        user_like = article.like_users.filter(pk=request.user.pk).exists()
    else:
        user_like = False
    like_count = article.like_users.all().count()
    comments = article.comment_set.order_by('-pk')
    comment_form = CommentForm()
    context = {
        'article': article,
        'user_like': user_like,
        'like_count': like_count,
        'comments': comments,
        'comment_form': comment_form,
    }
    return render(request, 'community/detail.html', context)


def create_comment(request, article_id):
    if not request.user.is_authenticated:
        return redirect('accounts:login')

    if request.method == 'POST':
        article = get_object_or_404(Article, pk=article_id)
        comment_form = CommentForm(request.POST)
        if comment_form.is_valid():
            comment = comment_form.save(commit=False)
            comment.user = request.user
            comment.article = article
            comment.save()
    return redirect('community:detail', article_id)


def delete_comment(request, article_id, comment_id):
    if not request.user.is_authenticated:
        return redirect('community:detail', article_id)

    comment = get_object_or_404(Comment, pk=comment_id)
    if request.user != comment.user:
        return redirect('community:detail', article_id)

    if request.method == 'POST':
        comment.delete()
    return redirect('community:detail', article_id)


def update(request, article_id):
    if not request.user.is_authenticated:
        return redirect('community:detail', article_id)

    article = get_object_or_404(Article, pk=article_id)
    if request.user != article.user:
        return redirect('community:detail', article.id)

    if request.method == 'POST':
        form = ArticleForm(request.POST, instance=article)
        if form.is_valid():
            form.save()
            return redirect('community:detail', article_id)
    else:
        form = ArticleForm(instance=article)
    context = {
        'form': form,
        'article': article,
    }
    return render(request, 'community/update.html', context)


def delete(request, article_id):
    if not request.user.is_authenticated:
        return redirect('community:detail', article_id)

    article = get_object_or_404(Article, pk=article_id)
    if request.user != article.user:
        return redirect('community:detail', article_id)

    if request.method == 'POST':
        article.delete()
    return redirect('community:index')


def like(request, article_id):
    if not request.user.is_authenticated:
        return redirect('community:detail', article_id)
    
    if request.method == 'POST':
        article = get_object_or_404(Article, pk=article_id)
        if article.like_users.filter(pk=request.user.pk).exists():
            article.like_users.remove(request.user)
        else:
            article.like_users.add(request.user)
    return redirect('community:detail', article_id)
    