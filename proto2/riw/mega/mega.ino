#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 200

NewPing sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo testeServo;
Servo mindinho;
Servo anelar;
Servo medio;
Servo indicador;
Servo dedao;
Servo dedaoPuxo;
Servo pulso;
Servo cotovelo;

bool idle = true;
void setup() {
    Serial.begin(115200);

    testeServo.attach(22);
    mindinho.attach(7);
    anelar.attach(3);
    medio.attach(4);
    indicador.attach(5);
    dedao.attach(2);
    dedaoPuxo.attach(6);
    pulso.attach(11);
    cotovelo.attach(10);

    // Idle
    mindinho.write(180);
    anelar.write(180);
    medio.write(180);
    indicador.write(180);
    dedao.write(180);
    dedaoPuxo.write(180);
    pulso.write(0); // 120 fecha
    cotovelo.write(180);

    testeServo.write(0);
}

void loop() {
    unsigned long int distancia = sensor.ping_cm();
    Serial.print("Distância: ");
    Serial.print(distancia);
    Serial.println("cm");

    String comando = Serial.readStringUntil('\n');

    if (idle) {
      if (distancia <= 10 && distancia != 0) {
        idle = false;
        // Cumprimento
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        pulso.write(170);
        cotovelo.write(180);
        delay(250);
        dedao.write(0);
        dedaoPuxo.write(0);

        delay(3000);

        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);

        idle = true;
      }
    }

    // Letras
    if (comando == "A") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(180);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "B") {
        idle = false;
        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        delay(1000);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "C") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(90);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(90);
    } else if (comando == "D") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(180);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "E") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(90);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "F") {
        idle = false;
        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(90);
        delay(500);
        dedao.write(135);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(90);
    } else if (comando == "G") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "I") {
        idle = false;
        mindinho.write(180);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        delay(1000);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "L") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "M") {
        idle = false;
        mindinho.write(0);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(170);
        cotovelo.write(180);
    } else if (comando == "N") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(180);
        indicador.write(180);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(170);
        cotovelo.write(180);
    } else if (comando == "O") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        pulso.write(0);
        cotovelo.write(90);
        delay(250);
        dedao.write(90);
        dedaoPuxo.write(0);
    } else if (comando == "J") {
        idle = false;
        mindinho.write(180);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(2000);

        pulso.write(170);

        delay(2000);

        cotovelo.write(90);

        delay(2000);

        cotovelo.write(180);

        delay(2000);
        
        pulso.write(0);
    } else if (comando == "Q") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(180);
        indicador.write(0);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(170);
        cotovelo.write(180);
    } else if (comando == "R") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(180);
        indicador.write(130);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "S") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        pulso.write(0);
        cotovelo.write(180);
        delay(250);
        dedao.write(0);
        dedaoPuxo.write(180);
    } else if (comando == "T") {
        idle = false;
        dedao.write(0);
        dedaoPuxo.write(0);
        delay(500);
        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(90);
        pulso.write(0);
        cotovelo.write(90);
    } else if (comando == "V") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(180);
        indicador.write(180);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "W") {
        idle = false;
        mindinho.write(0);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    } else if (comando == "Y") {
        idle = false;
        mindinho.write(180);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);
    }
    
    // Expressões
    else if (comando == "botaotail") {
        idle = false;
        dedao.write(180);
        dedaoPuxo.write(0);
        delay(500);
        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(0);
        pulso.write(0);
        cotovelo.write(90);

        delay(1500);

        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(180);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(1500);

        mindinho.write(180);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(1500);

        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);

        delay(2000);

        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);
        idle = true;
    } else if (comando == "botaoriw") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(180);
        indicador.write(90);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(1500);

        mindinho.write(180);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(1500);

        mindinho.write(0);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(2000);

        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);
        idle = true;
    } else if (comando == "botaoifrj") {
        idle = false;
        mindinho.write(180);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(1500);

        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(0);
        delay(500);
        dedao.write(180);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(90);

        delay(1500);

        mindinho.write(0);
        anelar.write(0);
        medio.write(180);
        indicador.write(90);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(1500);

        mindinho.write(180);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);

        delay(1000);

        pulso.write(170);

        delay(1000);

        cotovelo.write(90);

        delay(1000);
        
        pulso.write(0);

        delay(3000);

        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);
        idle = true;
    } else if (comando == "botaopalmas") {
        idle = false;
        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);

        delay(50);

        cotovelo.write(90);

        delay(1000);

        cotovelo.write(180);

        delay(1000);

        cotovelo.write(90);

        delay(1000);

        cotovelo.write(180);

        idle = true;
    }
    
    // Jogo
    else if (comando == "PEDRA") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(0);
        indicador.write(0);
        pulso.write(0);
        cotovelo.write(180);
        delay(250);
        dedao.write(0);
        dedaoPuxo.write(0);
    } else if (comando == "PAPEL") {
        idle = false;
        mindinho.write(180);
        anelar.write(180);
        medio.write(180);
        indicador.write(180);
        dedao.write(180);
        dedaoPuxo.write(180);
        pulso.write(0);
        cotovelo.write(180);

        delay(500);

        pulso.write(170);

        delay(500);

        pulso.write(0);
    } else if (comando == "TESOURA") {
        idle = false;
        mindinho.write(0);
        anelar.write(0);
        medio.write(180);
        indicador.write(180);
        dedao.write(0);
        dedaoPuxo.write(0);
        pulso.write(0);
        cotovelo.write(180);
    }

    else if (comando == "voltar") {
      idle = true;
      mindinho.write(180);
      anelar.write(180);
      medio.write(180);
      indicador.write(180);
      dedao.write(180);
      dedaoPuxo.write(180);
      pulso.write(0);
      cotovelo.write(180);
    }
}
