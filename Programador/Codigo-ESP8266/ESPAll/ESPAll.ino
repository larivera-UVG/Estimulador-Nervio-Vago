#include <ESP8266WiFi.h> // Librería para WiFi con ESP8266
#include <WiFiClient.h> // Librería para poder usar ESP8266 como cliente con protocolo TCP
#include <RCSwitch.h> // Librería para poder comunicar los módulos RF

const char* ssid     = "ARRIS-BD32"; // Nombre (Service Set Identifier) de la red WiFi
const char* password = "2PM7H7601455"; // Contraseña de la red WiFi

char dato, dato2, dato3, dato4, dato5; // Variables tipo char para leer los parámetros recibidos por WiFi
int modo, ancho, tiempo, freq, sleep; // Variables tipo int para almacenar los parámetros que se envían por RF
int mssg = 0;
int cond1, cond2, cond3, cond4, cond5 = 0;
byte modop[1]; // Arrays tipo byte para almacenar las lecturas por WiFi
byte anctime[2];
byte freqsleep[2];

int wifiFlag = 0;
int cont = 0; // Contador utilizado para recibir los 5 parámetros 

RCSwitch mySwitch = RCSwitch(); // Activación del módulo RF

WiFiServer servidorTCP(8266); // Declaración del puerto en el que se encuentra el Servidor
WiFiClient clienteTCP; // Declaración del nombre del cliente TCP

void setup() {
    
  Serial.begin(115200); // Se inicia la comunicación serial a una tasa de 115200
  delay(100); // Se esperan 100 ms para inicializar todo lo demás

  mySwitch.enableTransmit(4); // Módulo de transmisión RF conectado en el GPIO 4
  mySwitch.setProtocol(1); // Protocolo de transmisión 1 (por defecto) 
  
  Serial.print("\n Conectándose a: "); // Se indica la red a la que se está conectado
  Serial.println(ssid);


  WiFi.begin(ssid, password);  // Se intenta conectar a WiFi


  for(int k = 0; k < 20; k++){ // Se intenta conectar a la red cada 200 ms, 20 veces
    // La conexión a la red no es rápida, por lo que se debe dar varios intentos antes de declarar que la conexión no fue exitosa
    if(WiFi.status() != WL_CONNECTED){ // Si no está conectado a WiFi
      delay(200); // Volver a intentarlo después de 200 ms
    }
  }
  // Luego de los 20 intentos, se revisa si la conexión fue exitosa
  if(WiFi.status() != WL_CONNECTED) {  // Si no lo fue
    wifiFlag = 0; // Bandera de WiFi = 0
    
    Serial.println("No se pudo conectar con la red"); // Se coloca en el monitor serial que no se pudo conectar a la red
    Serial.println("Conectar cable USB a la computadora"); // Y que por favor se use el cable USB para comunicarse con la computadora
  }
  else{ // Si sí lo fue
    wifiFlag = 1; // Bandera de WiFi = 1
    
    Serial.print("Conectado, IP: "); // Se indica que la conexión a la red fue existosa
    Serial.println(WiFi.localIP()); // Se muestra en el monitor serial la IP del NodeMcu
    Serial.println(""); // Una línea en blanco para separar 

    servidorTCP.begin(); // Se inicializa el servidor TCP
  }

  

}

void loop() {

  if(wifiFlag == 1){ // Si la conexión fue exitosa
    if (!clienteTCP.connected()){ // Si el cliente no está conectado al servidor definido
       clienteTCP = servidorTCP.available(); // Se intenta conectar a cualquier servidor disponible
    } 
    else{ // Al conectar el cliente
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

        /* MODO DE OPERACION */
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

        // Envío de parámetros a Arduino Uno por medio de módulos RF
        mySwitch.send(modo, 8);
        mySwitch.send(ancho, 8);
        mySwitch.send(tiempo, 8);
        mySwitch.send(freq, 8);
        mySwitch.send(sleep, 8);

      
      }
             
    }
    
  }
  else{ // Si la conexión por WiFi no fue exitosa
      // Se procede a recibir datos por comunicación serial
      // Cada vez que se recibe un nuevo mensaje, se coloca un nueva condición en 1 para poder leer los 5 enviados desde la computadora sin errores
      if(Serial.available() & cond1 == 0){ // Si hay datos en el puerto serial
      mssg = Serial.read(); // Se lee el mensaje en mssg
      modop[0] = mssg; // Se almacena en el array correspondiente
      cond1 = 1; // Se coloca la condición en 1
    }
    if(Serial.available() & cond1 == 1 & cond2 == 0){
      mssg = Serial.read();
      anctime[0] = mssg;
      cond2 = 1;
    }
    if(Serial.available() & cond1 == 1 & cond2 == 1 & cond3 == 0){
      mssg = Serial.read();
      anctime[1] = mssg;
      cond3 = 1;
    }
    if(Serial.available() & cond1 == 1 & cond2 == 1 & cond3 == 1 & cond4 == 0){
      mssg = Serial.read();
      freqsleep[0] = mssg;
      cond4 = 1;
    }
    if(Serial.available() & cond1 == 1 & cond2 == 1 & cond3 == 1 & cond4 == 1 & cond5 == 0){
      mssg = Serial.read();
      freqsleep[1] = mssg;
      cond5 = 1;
    }

    // Al tener todas las condiciones en 1, indica que todos los mensajes fueron recibidos y almacenados
    if(cond1 == 1 & cond2 == 1 & cond3 == 1 & cond4 == 1 & cond5 == 1){ 
      cond1 = 0; // Se colocan todas las condiciones en 0 para poder recibir mensajes nuevos
      cond2 = 0;
      cond3 = 0;
      cond4 = 0; 
      cond5 = 0;

      // Dependiendo de lo recibido, se decide que parámetro va a ser el que se envíe

      /* MODO DE OPERACION */
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

      /* TIEMPO DE ESTIMULACION*/
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
      
      // Envío de parámetros a Arduino Uno por medio de módulos RF
      mySwitch.send(modo, 8);
      mySwitch.send(ancho, 8);
      mySwitch.send(tiempo, 8);
      mySwitch.send(freq, 8);
      mySwitch.send(sleep, 8);
    }
    
  }

}
