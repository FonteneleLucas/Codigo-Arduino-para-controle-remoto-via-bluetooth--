#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

int pinMotors[] = {4, 5, 7, 6};
//                EF, ET, DF, DT
int velocidade = 100;

void setup() {
  Serial.begin(9600);
  BTSerial.setTimeout(2);
  for (int i = 0; i < sizeof(pinMotors); i++) {
    pinMode(pinMotors[i], OUTPUT);
  }
  BTSerial.begin(38400);
}

void loop() {
  while (BTSerial.available() > 0) {
    String conteudo = BTSerial.readString();
    go(0,0);
    //Serial.println(conteudo);
    int velocidadeInput = conteudo.toInt();
    if (velocidadeInput > 0) {
      Serial.println(velocidadeInput);
      velocidade = velocidadeInput;
      Serial.println(velocidade);
    } else {
      //Serial.println("Comando normal");
      if (conteudo == "F") {
        go(velocidade, velocidade);
        Serial.println("Frente");
      } else if (conteudo == "B") {
        go(-velocidade, -velocidade);
        Serial.println("Tras");
      } else if (conteudo == "L") {
        go(-velocidade, velocidade);
        Serial.println("Esq");
      } else if (conteudo == "R") {
        go(velocidade, -velocidade);
        Serial.println("Dir");
      } else if (conteudo == "s") {
        go(0, 0);
        Serial.println("Stop");

      }
    }


  }

}

void go(int left, int right) {
  analogWrite(pinMotors[0], (left >= 0) ? left : 0);
  analogWrite(pinMotors[1], (left <= 0) ? -(left) : 0);
  analogWrite(pinMotors[2], (right >= 0) ? right : 0);
  analogWrite(pinMotors[3], (right <= 0) ? -(right) : 0);
}
