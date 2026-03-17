#include <SPI.h>
#include <RF24.h>

RF24 radio(4,5); // CE, CSN

const byte direccion[6] = "00001";

float distanciaRecibida;

void setup() {

  Serial.begin(115200);

  if (!radio.begin()) {
    Serial.println("NRF24L01 no detectado");
    while(1);
  }

  radio.openReadingPipe(0, direccion);
  radio.setChannel(112);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.println("Receptor listo, esperando datos...");
}

void loop() {

  if (radio.available()) {

    radio.read(&distanciaRecibida, sizeof(distanciaRecibida));

    Serial.print("Distancia recibida: ");
    Serial.print(distanciaRecibida);
    Serial.println(" cm");

  }

}