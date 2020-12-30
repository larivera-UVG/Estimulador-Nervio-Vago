#include <ESP8266WiFi.h> // Librería para WiFi con ESP8266
#include <WiFiClient.h> // Librería para poder usar ESP8266 como cliente con protocolo TCP
#include <LiquidCrystal_I2C.h> // Librería para poder utilizar la LCD I2C
#include <Wire.h> // Librería que permite la comunicación con dispositivos I2C
#include <RH_NRF24.h> // Librería para comunicarse con el nRF24L01+ por SPI

/**************************** MODIFICAR CON LOS DATOS DE LA RED ***************************/
const char* ssid = "ARRIS-BD32"; 
const char* password = "2PM7H7601455"; //2PM7H7601455
/******************************************************************************************/

/*************************************** NO MODIFICAR *************************************/
char dato, dato2, dato3, dato4, dato5; // Variables tipo char en las que se almacenan las lecturas de los parámetros por WiFi
//int modo, ancho, tiempo, freq, sleep; // Variables tipo int para almacenar los parámetros a enviar por RF
int mssg = 0; // Variable tipo int en la que se va almacenando la lectura del puerto serial
int cond1, cond2, cond3, cond4, cond5 = 0; // Condiciones para cambio de parámetro en la comunicación serial 
byte modop[1]; // MODIFICAR A CORRIENTE // Bytes para RF
byte anctime[2]; 
byte freqsleep[2]; 
uint8_t dataBus[6]; 

int wifiFlag = 0; // Bandera que indica si el ESP8266 se pudo conectar a la red WiFi
int cont = 0; // Contador de parámetros para la comunicación por WiFi
 
RH_NRF24 nrf24(2, 4); // Se declara el nRF24 con los pines en los que se va a conectar CSN y CE

LiquidCrystal_I2C lcd(0x27, 16, 2); // Se declara la pantalla LCD con dirección 0x27, 16 columnas y 2 filas

WiFiServer servidorTCP(8266); // Declaración del puerto en el que se encuentra el Servidor
WiFiClient clienteTCP; // Declaración del nombre del cliente TCP

void setup() {

  Serial.begin(115200); // Se inicializa la comunicación serial a una tasa de 115200
  while(!Serial); // Se espera a ésta se haya terminado de inicializar 
    ;

  Wire.begin(D3, D1); // Se declaran D3 y D1 como los pines para conectar SDA y SCL de la pantalla LCD
  lcd.begin(); // Se inicializa la pantalla LCD
  lcd.home(); // Se empieza a escribir en la posición (0,0) 
  lcd.clear(); // Se borra la pantalla para que inice limpia 

  nrf24.init(); // Se inicializa el nRF24L01+
  nrf24.setChannel(3); // Se utiliza el canal 3 para transmisión
  nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm); // Tasa de datos a 2 Mbps y Potencia de transmisión de 0 dBm

  /*if(!nrf24.init()) // Se revisa si se logró inicializar el nrf24
  {
    Serial.println("Incialización Fallida"); // Si falla, se escribe un mensaje en el monitor serial
  }
  if(!nrf24.setChannel(3)) // Se 
  {
    Serial.println("setChannel failed bitch");
  }
  if(!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
  {
    Serial.println("setRF failed");
  }*/
  
  //Serial.println("nRF24L01+ inicializado"); // Se indica en el monitor serial se incializó el nRF24L01+

  //Serial.print("\n Conectándose a: "); // Se indica la red a la que se está intentado conectar
  //Serial.println(ssid); 

  WiFi.begin(ssid, password); // Se intenta conectar a la red WiFi establecida

  for(int k = 0; k < 20; k++) // Se intenta conectar a la red cada 200 ms, 20 veces
  { // La conexión a la red no es rápida, por lo que se debe dar varios intentos antes de declarar que la conexión no fue exitosa
    if(WiFi.status() != WL_CONNECTED) // Si no está conectado a WiFi
    {
      delay(200); // Volver a intentarlo cada 200 ms
    }
  }

  // Luego de los 20 intentos, se revisa si la conexión fue exitosa por última vez 
  if(WiFi.status() != WL_CONNECTED) // Si no lo fue
  {
    wifiFlag = 0; // Bandera de WiFi apagada 
    
    //Serial.println("No se pudo conectar a la red"); // Se indica en el monitor serial que no fue exitosa la conexión
    //Serial.println("Conectar cable USB a la computadora"); 

    lcd.print("Conex. WiFi:"); // Se muestra en la pantalla LCD que no se pudo conectar a la red
    lcd.setCursor(0,1);
    lcd.print("No exitosa"); 
  }
  else // Si la conexión fue exitosa
  {
    wifiFlag = 1; // Bandera de WiFi encendida 

    Serial.print("Conectado, IP: "); // Se indica que la conexión fue exitosa
    Serial.println(WiFi.localIP()); // Se muestra la IP del NodeMcu
    Serial.println("");

    lcd.print("Conex. WiFi:");
    lcd.setCursor(0,1); 
    lcd.print("Exitosa"); 

    delay(3000);
    lcd.clear();
    
    lcd.print("IP: ");
    lcd.setCursor(0,1);
    lcd.print(WiFi.localIP()); // Se muestra la IP en la pantalla LCD

    servidorTCP.begin(); // Se inicializa el servidor TCP
  }

}

void loop() {

  if(wifiFlag == 1) // Si la conexión a la red WiFi fue exitosa 
  {
    if(!clienteTCP.connected()) // Si el cliente no está conectado al servidor definido 
    {
      clienteTCP = servidorTCP.available();
    }
    else
    {
      if(clienteTCP.available())
      {
        if(cont == 0)
        {
          dato = clienteTCP.read();
          modop[0] = dato; 
        }
        else if(cont == 1)
        {
          dato2 = clienteTCP.read(); 
          anctime[0] = dato2; 
        }
        else if(cont == 2)
        {
          dato3 = clienteTCP.read(); 
          anctime[1] = dato3; 
        }
        else if(cont == 3)
        {
          dato4 = clienteTCP.read();
          freqsleep[0] = dato4; 
        }
        else if(cont == 4)
        {
          dato5 = clienteTCP.read();
          freqsleep[1] = dato5; 
        }
        cont++; 
      }

      if(cont == 5)
      {
        cont = 0; 

        if(modop[0] == '1')
        {
          dataBus[0] = int(1); 
        }
        else if(modop[0] == '2')
        {
          dataBus[0] = int(2); 
        }
        else if(modop[0] == '3')
        {
          dataBus[0] = int(3); 
        }

        /* ANCHO DE PULSO */
        if(anctime[0] == '1'){
          dataBus[1] = int(1);
        }
        else if(anctime[0] == '2'){
          dataBus[1] = int(2);
        }
        else if(anctime[0] == '3'){
          dataBus[1] = int(3);
        }
        else if(anctime[0] == '4'){
          dataBus[1] = int(4);
        }
        else if(anctime[0] == '5'){
          dataBus[1]  = int(5);
        }

        /* TIEMPO DE ESTIMULACION */
        if(anctime[1] == '1'){
          dataBus[2] = int(1);
        }
        else if(anctime[1] == '2'){
          dataBus[2] = int(2);
        }
        else if(anctime[1] == '3'){
          dataBus[2] = int(3);
        }
        else if(anctime[1] == '4'){
          dataBus[2] = int(4);
        }
        else if(anctime[1] == '5'){
          dataBus[2] = int(5);
        }

        /* FRECUENCIA DE ESTIMULACION */
        if(freqsleep[0] == '1'){
          dataBus[3] = int(1);
        }
        else if(freqsleep[0] == '2'){
          dataBus[3] = int(2);
        }
        else if(freqsleep[0] == '3'){
          dataBus[3] = int(3);
        }
        else if(freqsleep[0] == '4'){
          dataBus[3] = int(4);
        }
        else if(freqsleep[0] == '5'){
          dataBus[3] = int(5);
        }
        else if(freqsleep[0] == '6'){
          dataBus[3] = int(6);
        }
        else if(freqsleep[0] == '7'){
          dataBus[3] = int(7);
        }
        else if(freqsleep[0] == '8'){
          dataBus[3] = int(8);
        }

        /* TIEMPO DE SLEEP */
        if(freqsleep[1] == '1'){
          dataBus[4] = int(1);
        }
        else if(freqsleep[1] == '2'){
          dataBus[4] = int(2);
        }

        nrf24.send(dataBus, sizeof(dataBus));
        nrf24.waitPacketSent(); 

        uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf); 

        if(nrf24.waitAvailableTimeout(1000))
        {
          if(nrf24.recv(buf, &len))
          {
            Serial.print("Mensaje recibido: ");
            Serial.println((char*)buf); 
            
            clienteTCP.write("1");
            lcd.clear(); 
            lcd.print("Param. Enviados"); 
            
          }
          else
          {
            Serial.println("Recepción fallida");
            lcd.clear(); 
            lcd.print("Fallo en com."); 
          }
        }
        else
        {
          Serial.println("Sin respuesta");    
        }
        delay(5000);
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
      //lcd.setCursor(0,1);
      //lcd.print("Sent 1");
    }
    if(Serial.available() & cond1 == 1 & cond2 == 0){
      mssg = Serial.read();
      anctime[0] = mssg;
      cond2 = 1;
      //lcd.setCursor(0,1);
      //lcd.print("Sent 2");
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
      if(modop[0] == '1')
      {
        dataBus[0] = int(1);
      }
      else if(modop[0] == '2')
      {
        dataBus[0] = int(2);
      }
      else if(modop[0] == '3')
      {
        dataBus[0] = int(3);
      }

      /* ANCHO DE PULSO */
      if(anctime[0] == '1')
      {
        dataBus[1] = int(1);
      }
      else if(anctime[0] == '2')
      {
        dataBus[1] = int(2);
      }
      else if(anctime[0] == '3')
      {
        dataBus[1] = int(3);
      }
      else if(anctime[0] == '4')
      {
        dataBus[1] = int(4);
      }
      else if(anctime[0] == '5')
      {
        dataBus[1] = int(5);
      }

      /* TIEMPO DE ESTIMULACION*/
      if(anctime[1] == '1')
      {
        dataBus[2] = int(1);
      }
      else if(anctime[1] == '2')
      {
        dataBus[2] = int(2);
      }
      else if(anctime[1] == '3')
      {
        dataBus[2] = int(3);
      }
      else if(anctime[1] == '4')
      {
        dataBus[2] = int(4);
      }
      else if(anctime[1] == '5')
      {
        dataBus[2] = int(5);
      }

      /* FRECUENCIA DE ESTIMULACION */
      if(freqsleep[0] == '1')
      {
        dataBus[3] = int(1);
      }
      else if(freqsleep[0] == '2')
      {
        dataBus[3] = int(2);
      }
      else if(freqsleep[0] == '3')
      {
        dataBus[3] = int(3);
      }
      else if(freqsleep[0] == '4')
      {
        dataBus[3] = int(4);
      }
      else if(freqsleep[0] == '5')
      {
        dataBus[3] = int(5);
      }
      else if(freqsleep[0] == '6')
      {
        dataBus[3] = int(6);
      }
      else if(freqsleep[0] == '7')
      {
        dataBus[3] = int(7);
      }
      else if(freqsleep[0] == '8')
      {
        dataBus[3] = int(8);
      }

      /* TIEMPO DE SLEEP */
      if(freqsleep[1] == '1')
      {
        dataBus[4] = int(1);
      }
      else if(freqsleep[1] == '2')
      {
        dataBus[4] = int(2);
      }

      nrf24.send(dataBus, sizeof(dataBus));
      nrf24.waitPacketSent(); 

      uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(buf); 

      if(nrf24.waitAvailableTimeout(1000))
      {
        if(nrf24.recv(buf, &len))
        {
          //Serial.print("RMensaje recibido: ");
          //Serial.println((char*)buf); 
            
          Serial.print("1");
          lcd.clear(); 
          lcd.print("Confirmacion");
          lcd.setCursor(0,1);
          lcd.print("Recibida"); 
            
        }
        else
        {
          Serial.println("Recepción fallida");
          lcd.clear(); 
          lcd.print("Fallo en com."); 
        }
      }
      else
      {
        //Serial.println("Sin respuesta");    
      }
      delay(5000);
    
    }
    
  }
}
