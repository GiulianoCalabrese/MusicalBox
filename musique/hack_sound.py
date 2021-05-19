import pygame##from pygame ##import mixer
import urllib
import sys

if sys.version_info[0] == 3:
    from urllib.request import urlopen
else:
    from urllib import urlopen

while 1:
    with urlopen("http://161.105.212.131/lora_0004A30B001EC8BE/raw.php") as url:
        s = url.read()
    PL = s.decode("utf8")
    url.close()
    ##print(int(PL[83:91],16))
    temp = int(PL[83:84],16)
    humy = int(PL[85:86],16)
    Lumy = int(PL[87],16)
    gas = int(PL[88:89],16)
    Vent = int(PL[90:91],16)

    pygame.mixer.init()
    pygame.mixer.pre_init(44100, -16, 2, 2048)
    pygame.init()
    sounds = []
    if temp < 10  :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_temperature_cold.ogg'))
    elif temp > 20 :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_temperature_warm.ogg'))
    else :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_temperature_medium.ogg'))
        
    if humy < 30 :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_rain_light.ogg'))
    elif humy >60 :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_rain_hard.ogg'))
    else :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_rain_medium.ogg'))
        
    if Vent < 8 :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_wind_low.ogg'))
    elif Vent > 24 :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_wind_high.ogg'))
    else :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_wind_medium.ogg'))
        
    if gas < 40 :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_air_quality_good.ogg'))
    elif gas > 50 :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_air_quality_bad.ogg'))
    else :
        sounds.append(pygame.mixer.Sound('/home/pi/Desktop/03_air_quality_medium.ogg'))

    for sound in sounds:
        sound.play(60)
