from django.shortcuts import render
from django.http import HttpResponse
from django.utils import timezone
from main.models import Motion
from django.core.mail import send_mail

# Create your views here.
def main(request):
    return render(request,'main.html', {"motions" : Motion.objects.all()})


def send_data(request):
    new_state = bool(int(request.POST["new_state"]))
    time = datetime.now()

    m = Motion(new_state = new_state, time = timezone.now())
    m.save()

    if (new_state)
    send_mail(
    'Motion Detected',
    'Motion Detected!',
    'testapp545545',
    ['anik545@gmail.com'],
    fail_silently=False)


    return HttpResponse(status=200)