from django.shortcuts import render
from django.http import HttpResponse
from django.utils import timezone
from main.models import Motion

# Create your views here.
def main(request):
    return render(request,'main.html', {"motions" : Motion.objects.all()})


def send_data(request):
    new_state = request.POST["new_state"]
    time = datetime.now()

    m = Motion(new_state = new_state, time = timezone.now())
    m.save()

    return HttpResponse(status=200)