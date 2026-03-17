Práctica NFR24L01 - Envío de datos con generador de señal

Integrantes: 

Luis Arturo Cruz Coria
Axel Johab Rodríguez Ortiz

Video demostrativo 
https://youtu.be/ih40Ne9ch1g
Github
https://github.com/arturocruz-0503/Pr-ctica-NFR24L01---Env-o-de-datos-con-generador-de-se-al 

Objetivo del proyecto.

Utilizando el módulo NRF24L01, establecer la comunicación inalámbrica entre dos dispositivos, creando el entorno necesario para que uno de ellos funcione como transmisor (TX) y el otro como receptor (RX). El objetivo se cumple cuando, al monitorear la terminal del dispositivo receptor, se muestre un mensaje indicando que la comunicación se ha establecido correctamente y se visualicen periódicamente los valores enviados y recibidos provenientes de un generador de señales.

Descripción del proyecto.

El proyecto consiste en implementar un sistema de comunicación inalámbrica entre dos dispositivos mediante el uso de módulos NRF24L01, donde uno de ellos será configurado como transmisor (TX) y el otro como receptor (RX). La comunicación se llevará a cabo utilizando radiofrecuencia en la banda de 2.4 GHz, lo que permite la transmisión de datos de manera eficiente y en tiempo real.
El dispositivo configurado como transmisor se encargará de generar y enviar señales de manera periódica, las cuales serán transmitidas a través del módulo NRF24L01. Estas señales provienen de un sensor ultrasónico conectado al microcontrolador.
Por otro lado, el dispositivo configurado como receptor recibirá la información enviada, la procesará y mostrará los valores en la terminal serial. Además, al establecerse correctamente la comunicación, se mostrará un mensaje de confirmación en la terminal del receptor, permitiendo verificar el correcto funcionamiento del sistema.
Durante la ejecución del programa, se podrá observar en la terminal del receptor la recepción continua de datos, demostrando así que están conectadas correctamente ambas antenas

Conexiones

ESP32

Pin	GPIO ESP32	Descripción
VCC	VCC 3.3V	Alimentación 3.3V (IMPORTANTE NO CONECTAR A 5V)
GND	GND	Tierra
CE	4	Habilita la transmisión o recepción
CSN	5	Selección del dispositivo SPI
SCK	18	Reloj SPI
MOSI	23	Datos del microcontrolador al módulo
MISO	19	Datos del módulo al microcontrolador
IRQ	No conectado	Interrupción

Arduino

Pin	Pin Arduino	Descripción
Sensor VCC	5V	Alimentación 5V
Sensor GND	GND	Tierra
Sensor TRIG	6	Pin de disparo que envía un pulso para medir distancia
Sensor ECHO	7	Pin de recepción que devuelve el tiempo del pulso reflejado para calcular distancia
NRF24L01 VCC	3.3V	Alimentación 3.3V (IMPORTANTE NO CONECTAR A 5V)
NRF24L01 GND	GND	Tierra
NRF24L01 CE	9	Habilita la transmisión o recepción
NRF24L01 CSN	10	Selección del dispositivo SPI
NRF24L01 SCK	13	Reloj SPI
NRF24L01 MOSI	11	Datos del microcontrolador al módulo
NRF24L01 MISO	12	Datos del módulo al microcontrolador
NRF24L01  IRQ	No conectado	Interrupción

Lógica de funcionamiento del programa

1. Inicialización

En ambos dispositivos (TX y RX) se inicializa la comunicación mediante el módulo NRF24L01 utilizando la interfaz SPI.
Se configura la misma dirección de comunicación ("00001"), el canal de transmisión (canal 112) y el nivel de potencia (RF24_PA_LOW), asegurando que ambos módulos puedan comunicarse correctamente.

En el transmisor (Arduino) se configura el módulo en modo escritura con openWritingPipe() y se desactiva la escucha con stopListening().

En el receptor (ESP32) se configura el módulo en modo lectura con openReadingPipe() y se activa la escucha con startListening().

Además, se inicializa la comunicación serial en ambos dispositivos para monitorear el funcionamiento.

2. Funcionamiento del transmisor (TX)

El transmisor tiene conectado un sensor ultrasónico mediante los pines TRIG y ECHO.
Se genera un pulso de activación en el pin TRIG para emitir una onda ultrasónica.
El pin ECHO recibe el rebote de la señal, midiendo el tiempo que tarda en regresar.

Con este tiempo (duracion), se calcula la distancia utilizando la fórmula:

distancia= (duración * 0.034)/2

El valor de la distancia se envía mediante el módulo NRF24L01 usando radio.write().

Después del envío:

Si la transmisión es exitosa, se muestra en la terminal el valor enviado.
Si ocurre un error, se indica en la terminal.

Este proceso se repite cada segundo, enviando datos de forma periódica.

3. Funcionamiento del receptor (RX)

El receptor permanece en modo escucha constante esperando datos.
Se verifica si hay información disponible con radio.available().
Cuando se reciben datos, se leen con radio.read() y se almacenan en la variable distanciaRecibida.
El valor recibido se muestra en la terminal serial, indicando la distancia en centímetros.

4. Comunicación entre dispositivos

El sistema funciona mediante el envío continuo de datos desde el transmisor hacia el receptor.
El transmisor mide la distancia con el sensor ultrasónico.
Envía ese valor por radiofrecuencia.
El receptor recibe el dato y lo muestra en la terminal.
La comunicación es unidireccional (TX → RX) y se mantiene activa mientras ambos dispositivos estén encendidos y correctamente configurados.

Para ejecutar:

1.- Instalar el software necesario

Instalar el Arduino IDE en la computadora.
Instalar el soporte para placas ESP32 en el Arduino IDE.
Instalar la librería RF24:
	Ir a Herramientas → Administrar bibliotecas
	Buscar RF24
	Instalar la librería desarrollada por TMRh20.

2.- Realizar las conexiones
Conectar el módulo NRF24L01 al ESP32 (receptor) según la tabla de conexiones.
Conectar el módulo NRF24L01 al Arduino (transmisor) según la tabla de conexiones.
Conectar el sensor ultrasónico al Arduino (igualmente incluído en la tabla de conexiones):
TRIG al pin 6
ECHO al pin 7
VCC a 5V
GND a tierra

3.- Configurar el código del transmisor (Arduino con sensor)

Abrir Arduino IDE.
Crear un nuevo sketch.
Copiar el código del transmisor.
Seleccionar la placa Arduino (UNO o la que estés usando).
Seleccionar el puerto COM correspondiente.
Cargar el programa en el Arduino.

4.- Configurar el código del receptor (ESP32)

Abrir otro sketch en Arduino IDE.
Copiar el código del receptor.
Seleccionar la placa ESP32.
Seleccionar el puerto correspondiente.
Subir el programa al ESP32.

5.- Abrir el monitor serial

Abrir el Monitor Serial en ambos dispositivos.
Configurar la velocidad:
ESP32 (RX): 115200 baudios
Arduino (TX): 9600 baudios

6.- Verificar funcionamiento

En el transmisor se deben mostrar los valores de distancia enviados.
En el receptor se debe mostrar el mensaje: “Receptor listo, esperando datos…”
Posteriormente, se deben visualizar los valores de distancia recibidos en tiempo real.

Si el sistema no funciona:

Verificar que el NRF24L01 esté alimentado con 3.3V.

Revisar que todos los cables estén bien conectados.

Confirmar que ambos códigos usen la misma dirección ("00001").

Verificar que ambos usen el mismo canal (112).

Revisar que la librería RF24 esté instalada correctamente.
