import serial # pySerial
import pygame # Conexão com a placa Zero Delay
import vlc # Player de video - python-vlc
from threading import Thread # Para loop infinito do video
from time import sleep # Delay

TEMPOLOOP = 6

laires = serial.Serial("/dev/ttyUSBX", 115200) # ou "COMX", sendo X dependendo da porta

pygame.joystick.init()
# Para Raspberry:
joystick = pygame.joystick.Joystick(0)
joystick.init()
# Para Windows:
# joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
# if len(joysticks) == 0:
#     raise Exception("Placa Zero Delay não conectada!")

player = vlc.MediaPlayer() 
player.set_fullscreen(True)

def threadLoop():
    def loop():
        sleep(0.5)
        if not(player.is_playing()):
            player.set_media(vlc.Media("loop.mp4"))
            player.play()
            sleep(TEMPOLOOP)
        loop()
    loop()

def play(video = "escolhabotao"): # O parâmetro video é o nome do arquivo
    global selection
    player.set_media(vlc.Media(video + ".mp4")) 
    player.play()
    sleep(4)
    while player.is_playing():
        sleep(0.1)
    selection = False

Thread(target=threadLoop).start()
pygame.init()
print("TAIL Iniciado")
selection = False
while True:
    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONDOWN: # Espera o clique nos botões
            if event.dict['button']:
                if selection:
                    if event.dict['button'] == 0:
                        print('auditorio')
                        laires.write(b'auditorio')
                        play("auditorio")
                    if event.dict['button'] == 1:
                        print('banheiro')
                        laires.write(b'banheiro')
                        play("banheiro")
                    if event.dict['button'] == 2:
                        print('secretaria')
                        laires.write(b'secretaria')
                        play("secretaria")
                    else:
                        print(event.dict['button'])
                else: 
                    selection = True
                    Thread(target=play).start()
    print(laires.readline())