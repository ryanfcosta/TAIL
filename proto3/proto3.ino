#include <Servo.h>

#define H 180
#define AH 0

Servo trapezioE;
Servo trapezioD;
Servo ombroE;
Servo ombroD;
Servo bicepsE;
Servo bicepsD;
Servo cotoveloE;
Servo cotoveloD;
Servo cabeca;

void setup() {
    Serial.begin(115200);
    
    trapezioE.attach(2); //
    trapezioD.attach(4); //
    ombroE.attach(9); //
    ombroD.attach(3); //
    bicepsE.attach(7); //
    bicepsD.attach(8); //
    cotoveloE.attach(10);
    cotoveloD.attach(6); //
    cabeca.attach(5); //
}

void loop() {
    String comando = Serial.readStringUntil('\n');
    Serial.println(comando);

    if (comando == "auditorio") {
      mover(bicepsE, H, 500);
      mover(bicepsD, AH, 80);
      delay(500);
      mover(bicepsE, AH, 100);
      mover(bicepsD, H, 80);
      delay(500);
      mover(bicepsE, H, 500);
      mover(bicepsD, AH, 80);
      delay(500);
      mover(bicepsE, AH, 100);
      mover(bicepsD, H, 80);
      delay(500);
      mover(bicepsE, H, 500);
      mover(bicepsD, AH, 80);
      delay(500);
      mover(bicepsE, AH, 100);
      mover(bicepsD, H, 80);
    } else if (comando == "banheiro") {
      mover(trapezioE, AH, 700);
      mover(trapezioD, H, 700);
      delay(2000);
    } else if (comando == "secretaria") {
      mover(cabeca, AH, 100);
      mover(ombroD, H, 500);
      delay(250);
      mover(cabeca, H, 70);
    }
}

void mover(Servo servo, int direcao, int duracao) {
  servo.write(direcao);
  delay(duracao);
  servo.write(90);
}

// Exemplo:
// Esse exemplo move o servo na direção horária com velocidade definida por H durante um segundo
// mover(servo, H, 1000);