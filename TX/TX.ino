#include <SPI.h>
#include <RF24.h>

RF24 radio(9,10); // CE, CSN

const byte direccion[6] = "00001";

#define TRIG 6
#define ECHO 7

long duracion;
float distancia;

void setup() {

  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  if (!radio.begin()) {
    Serial.println("NRF24L01 no detectado");
    while(1);
  }

  radio.openWritingPipe(direccion);
  radio.setChannel(112);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  Serial.println("Transmisor listo con sensor ultrasonico");
}

void loop() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duracion = pulseIn(ECHO, HIGH);

  distancia = duracion * 0.034 / 2;

  bool enviado = radio.write(&distancia, sizeof(distancia));

  if(enviado){
    Serial.print("Distancia enviada: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }
  else{
    Serial.println("Error al enviar");
  }

  delay(1000);
}