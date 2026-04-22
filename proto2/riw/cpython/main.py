from flask import Flask, Response, render_template
import serial
import cv2
from time import sleep
import random
import mediapipe as mp

# Configuração da detecção dos gestos
biblioteca = mp.solutions.hands
interpretador = biblioteca.Hands(max_num_hands=1)

statusJogador = {
    "dedao": "aberto",
    "indicador": "aberto",
    "medio": "aberto",
    "anelar": "aberto",
    "mindinho": "aberto"
}

statusPedra = {
    "dedao": "fechado",
    "indicador": "fechado",
    "medio": "fechado",
    "anelar": "fechado",
    "mindinho": "fechado"
}

statusPapel = {
    "dedao": "aberto",
    "indicador": "aberto",
    "medio": "aberto",
    "anelar": "aberto",
    "mindinho": "aberto"
}

statusTesoura = {
    "dedao": "fechado",
    "indicador": "aberto",
    "medio": "aberto",
    "anelar": "fechado",
    "mindinho": "fechado"
}

statusSalvos = {"PEDRA": statusPedra, "PAPEL": statusPapel, "TESOURA": statusTesoura}

laires = serial.Serial('COM8', 115200)

labels = ["PEDRA", "PAPEL", "TESOURA"]
status = ""
jogo_ocorrido = False

conn = cv2.VideoCapture(0)
if not conn.isOpened():
    print("Não foi possível se conectar com a câmera!")
    exit()
conn.set(cv2.CAP_PROP_EXPOSURE, 0.5)

server = Flask("")

@server.route('/')
def handleRoot():
    return render_template("index.html")

@server.route('/camera')
def streamPython():
    def stream():
        global status, jogo_ocorrido
        jogo_ocorrido = False
        while True:
            retorno, img = conn.read()
            img = cv2.flip(img, 1)
            imgBytes = cv2.imencode('.jpg', img)[1].tobytes()
            imgRGB = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
            resultado = interpretador.process(imgRGB)
            pontosMao = resultado.multi_hand_landmarks
            altura, largura, _ = img.shape
            pontos = []

            if pontosMao:
                for ponto in pontosMao:
                    for coordenada in ponto.landmark:
                        pontos.append((int(coordenada.x * largura), int(coordenada.y * altura)))
                    
                    dedos = [("indicador", 8), ("medio", 12), ("anelar", 16), ("mindinho", 20)]
                    if pontos:
                        if ponto.landmark[biblioteca.HandLandmark.WRIST].x < 0.5:
                            statusJogador["dedao"] = "fechado" if  pontos[4][0] < pontos[3][0] else "aberto"
                        else:
                            statusJogador["dedao"] = "fechado" if  pontos[3][0] < pontos[4][0] else "aberto"
                        for x in dedos:
                            statusJogador[x[0]] = "aberto" if pontos[x[1]][1] < pontos[x[1]-2][1] else "fechado"
            
            for teste in statusSalvos:
                if statusSalvos[teste] == statusJogador:
                    if not jogo_ocorrido:
                        jogadaTail = random.randint(0, 2)

                        if teste == labels[jogadaTail]:
                            resultado = "EMPATE"
                        elif (teste == "PEDRA" and labels[jogadaTail] == "TESOURA") or (teste == "TESOURA" and labels[jogadaTail] == "PAPEL") or (teste == "PAPEL" and labels[jogadaTail] == "PEDRA"):
                            resultado = "JOGADOR"
                        else:
                            resultado = "TAIL"

                        status = teste + "," + labels[jogadaTail] + "," +  resultado
                        laires.write(b'' + labels[jogadaTail].encode())
                        jogo_ocorrido = True



            yield(b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + imgBytes + b'\r\n')
    return Response(stream(), mimetype='multipart/x-mixed-replace; boundary=frame')

@server.route("/<path>")
def comandoPath(path):
    print(path)
    laires.write(b'' + path.encode())
    sleep(2)
    return Response((yield(b'Recebido')), mimetype='text/html')

@server.route("/jogoStatus")
def jogoStatus():
    if jogo_ocorrido:
        return Response((yield(b'' + status.encode())), mimetype='text/html')


server.run(host='localhost', port=80)
