/**
 * Creado por Miguel Alvarez - 16168
 * Universidad del Valle de Guatemala - Facultad de Ingeniería
 * Departamento de Ingeniería Mecatrónica
 * Módulo de Programación - Proyecto de Neuroestimulación del Nervio Vago 
 * Fase 2
 * 
 * 
 * Archivo NMRecRF -> Recepción de datos por RF con el módulo RF de 433 MHz
 **/
 
#include <RCSwitch.h> // Se incluye la librería para manejar los módulos RF

RCSwitch mySwitch = RCSwitch(); // Se declara el nombre para el módulo RF

int i = 0; // Contador de recepciones
int k = 0; // Indicador de parámetro
int value; // Variable para almacenar la lectura RF
int slcond = 0; // Condición que se activa cuando dependiendo si se recibió 4 o 5 veces el quinto parámetro

void setup() {
  Serial.begin(115200); // Comunicación serial habilitada a 115200 baudios
  mySwitch.enableReceive(0);  // Interrupción en el Pin 2
}

void loop() {
  if (mySwitch.available()) { // Si hay información disponible 

    if(i == 0 & k == 0){ // Si es el primer parámetro y no se ha recibido nada
      value = mySwitch.getReceivedValue(); // Se recibe el parámetro
      Serial.print("Modo: ");
      if(value == 1){
        Serial.println("Estimulación"); // Se muestra el parámetro en el monitor Serial
      }
      else if(value == 2){
        Serial.println("Iman");
      }
      else if(value == 3){
        Serial.println("Reposo");
      }
    }
    else if(i == 0 & k == 1){ // Segundo parámetro
      value = mySwitch.getReceivedValue();
      Serial.print("Ancho de pulso: ");
      if(value == 1){
        Serial.println("25%");
      }
      else if(value == 2){
        Serial.println("30%");
      }
      else if(value == 3){
        Serial.println("50%");
      }
      else if(value == 4){
        Serial.println("75%");
      }
      else if(value == 5){
        Serial.println("100%");
      }
    }
    else if(i == 0 & k == 2){ // Tercer parámetro
      value = mySwitch.getReceivedValue();
      Serial.print("Tiempo de estimulación:  ");
      if(value == 1){
        Serial.println("Tiempo 1");
      }
      else if(value == 2){
        Serial.println("Tiempo 2");
      }
      else if(value == 3){
        Serial.println("Tiempo 3");
      }
      else if(value == 4){
        Serial.println("Tiempo 4");
      }
      else if(value == 5){
        Serial.println("Tiempo 5");
      }
    }
    else if(i == 0 & k == 3){ // Cuarto parámetro
      value = mySwitch.getReceivedValue();
      Serial.print("Frecuencia:  ");
      if(value == 1){
        Serial.println("490.20 Hz (Por defecto)");
      }
      else if(value == 2){
        Serial.println("30.64 Hz");
      }
      else if(value == 3){
        Serial.println("122.50 Hz");
      }
      else if(value == 4){
        Serial.println("245.10 Hz");
      }
      else if(value == 5){
        Serial.println("980.39 Hz");
      }
      else if(value == 6){
        Serial.println("3921.16 Hz");
      }
      else if(value == 7){
        Serial.println("31372.55 Hz");
      }
      else if(value == 8){
        Serial.println("Frecuencia 8");
      }
    }
    else if(i == 0 & k == 4){ // Quinto parámetro
      value = mySwitch.getReceivedValue();
      Serial.print("Tiempo de apagado:  ");
      if(value == 1){
        Serial.println("5 min");
      }
      else if(value == 2){
        Serial.println("NO");
      }
    }
    else if(i == 5 & k == 4){ // Si se recibió un quinto valor del quinto parámetro
      slcond = 1; // Se activa la condición
    }
    mySwitch.resetAvailable(); // Se resetea la lectura RF
    i++; // Se aumenta el contador de recepciones
    
  }

  
  if(i == 4 & k == 0){ // Si fueron 4 recepciones del primer parámetro
    i = 0; // Se resetea el número de recepciones
    k = 1; // Se aumenta el indicador de parámetro
  }
  else if(i == 5 & k == 1){ // 5 recepciones del segundo parámetro
    i = 0;
    k = 2;
  }
  else if(i == 5 & k == 2){ // 5 recepciones del tercer parámetro
    i = 0;
    k = 3;
  }
  else if(i == 5 & k == 3){ // 5 recepciones del cuarto parámetro
    i = 0;
    k = 4;
  }
  else if(i == 5 & k == 4){ // 5 recepciones del quinto parámetro
    i = 0;
    k = 5;
    slcond = 0; // Se desactiva la condición 
  }

  if(k == 5){ // Si se leyeron todos los parámetros
    k = 0; // Resetear el indicador de parámetros
    Serial.println("");
  }
}
