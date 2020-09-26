#include <ESP8266WiFi.h> // Librería para WiFi con ESP8266
#include <WiFiClient.h> // Librería para poder usar ESP8266 como cliente con protocolo TCP
#include <RCSwitch.h> // Librería para poder comunicar los módulos RF

const char* ssid     = "ARRIS-BD32"; // Nombre (Service Set Identifier) de la red WiFi
const char* password = "2PM7H7601455"; // Contraseña de la red WiFi

char dato, dato2, dato3, dato4, dato5; // Variables tipo char para leer los parámetros recibidos por WiFi
int modo, ancho, tiempo, freq, sleep; // Variables tipo int para almacenar los parámetros que se envían por RF
byte modop[1]; // Arrays tipo byte para almacenar las lecturas por WiFi
byte anctime[2];
byte freqsleep[2];

int cont = 0; // Contador utilizado para recibir los 5 parámetros 

RCSwitch mySwitch = RCSwitch(); // Activación del módulo RF

WiFiServer servidorTCP(8266); // Declaración del puerto en el que se encuentra el Servidor
WiFiClient clienteTCP; // Declaración del nombre del cliente TCP

void setup() {
    
  Serial.begin(115200); // Se inicia la comunicación serial a una tasa de 115200
  delay(100); // Se esperan 100 ms para inicializar todo lo demás

  mySwitch.enableTransmit(4); // Módulo de transmisión RF conectado en el GPIO 4
  mySwitch.setProtocol(1); // Protocolo de transmisión 1 (por defecto) 
  
  Serial.print("Conectandose a: "); // Se indica la red a la que se está conectado
  Serial.println(ssid);


  WiFi.begin(ssid, password);  // Se intenta conectar a WiFi
  
  while (WiFi.status() != WL_CONNECTED) {  // Esperar a que se conecte a WiFi
    delay(200); // Cada 200 ms se intenta conectar de nuevo si no se logra conectar
  }

  Serial.print("Conectado, IP: "); // Se indica que la conexión a la red fue existosa
  Serial.println(WiFi.localIP()); // Se muestra en el monitor serial la IP del NodeMcu
  Serial.println("");

  servidorTCP.begin(); // Se inicializa el servidor TCP

}

void loop() {
  
  if (!clienteTCP.connected()){ // Si el cliente no está conectado al servidor definido
        clienteTCP = servidorTCP.available(); // Se intenta conectar a cualquier servidor disponible
  } 
  else{ // Si sí le logró la conexión 
    if (clienteTCP.available()){ // Mientras hayan datos disponibles por WiFi
      if(cont == 0){ // Si es el primer parámetro
        dato = clienteTCP.read(); // Se lee en dato
        modop[0] = dato; // Y se almacena en el array de modo
      }
      else if(cont == 1){ // Si es el segundo parámetro
        dato2 = clienteTCP.read();
        anctime[0] = dato2; // Se almacena en la primera casilla (ancho) del array de ancho y tiempo 
      }
      else if(cont == 2){ // Si es el tercer parámetro
        dato3 = clienteTCP.read(); 
        anctime[1] = dato3; // Se almacena en la segunda casilla (tiempo) del array de ancho y tiempo
      }
      else if(cont == 3){ // Si es el cuarto parámetro
        dato4 = clienteTCP.read(); 
        freqsleep[0] = dato4; // Se almacena en la primera casilla (frecuencia) del array de frecuencia y tiempo de sleep
      }
      else if(cont == 4){ // Si es el quinto parámetro 
        dato5 = clienteTCP.read(); 
        freqsleep[1] = dato5; // Se almacena en la segunda casilla (tiempo de sleep) del array de frecuencia y tiempo de sleep
      }
      cont++; // Se aumenta el contador
    }

    if(cont == 5){ // Cuando el contador llega a 5, los 5 parámetros han sido recibidos y almacenados
      cont = 0; // Se reinicia al contador para poder recibir de nuevo cuando se solicite

      // Dependiendo de lo recibido, se decide que parámetro va a ser el que se envíe

      /* MODO DE ESTIMULACION */
      if(modop[0] == '1'){
        modo = int(1);
      }
      else if(modop[0] == '2'){
        modo = int(2);
      }
      else if(modop[0] == '3'){
        modo = int(3);
      }

      /* ANCHO DE PULSO */
      if(anctime[0] == '1'){
        ancho = int(1);
      }
      else if(anctime[0] == '2'){
        ancho = int(2);
      }
      else if(anctime[0] == '3'){
        ancho = int(3);
      }
      else if(anctime[0] == '4'){
        ancho = int(4);
      }
      else if(anctime[0] == '5'){
        ancho = int(5);
      }

      /* TIEMPO DE ESTIMULACION */
      if(anctime[1] == '1'){
        tiempo = int(1);
      }
      else if(anctime[1] == '2'){
        tiempo = int(2);
      }
      else if(anctime[1] == '3'){
        tiempo = int(3);
      }
      else if(anctime[1] == '4'){
        tiempo = int(4);
      }
      else if(anctime[1] == '5'){
        tiempo = int(5);
      }
    
      /* FRECUENCIA DE ESTIMULACION */
      if(freqsleep[0] == '1'){
        freq = int(1);
      }
      else if(freqsleep[0] == '2'){
        freq = int(2);
      }
      else if(freqsleep[0] == '3'){
        freq = int(3);
      }
      else if(freqsleep[0] == '4'){
        freq = int(4);
      }
      else if(freqsleep[0] == '5'){
        freq = int(5);
      }
      else if(freqsleep[0] == '6'){
        freq = int(6);
      }
      else if(freqsleep[0] == '7'){
        freq = int(7);
      }
      else if(freqsleep[0] == '8'){
        freq = int(8);
      }

      /* TIEMPO DE SLEEP */
      if(freqsleep[1] == '1'){
        sleep = int(1);
      }
      else if(freqsleep[1] == '2'){
        sleep = int(2);
      }

      // Envio de parámetros a Arduino Uno por medio de módulos RF
      mySwitch.send(modo, 8);
      mySwitch.send(ancho, 8);
      mySwitch.send(tiempo, 8);
      mySwitch.send(freq, 8);
      mySwitch.send(sleep, 8);

      
    }
             
  }

}
