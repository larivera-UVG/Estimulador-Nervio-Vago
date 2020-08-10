/* SendTry.ino - PROGRAMA PARA RECIBIR DATOS DE UNA TERMINAL SERIAL Y ENVIAR A OTRO ARDUINO
 *  Miguel Alvarez - 16168
 */

/*********************************************************************
 * Librerías Utilizadas
 ********************************************************************/
#include <stdlib.h>

/*********************************************************************
 * Declaración de variables
 ********************************************************************/
String cadena; // Variable para almacener la lectura del puerto serial
byte lec[8]; // Array para almacenar las conversiones a enteros de la lectura
int i = 0; // Contador de lecturas
unsigned int intput; // Variable para almacenar la conversión a entero de la lectura

void setup() {
  Serial1.begin(9600); // Inicialización del puerto serial 1 y 2
  Serial2.begin(9600); 

  Serial1.setTimeout(100); // Timeout de 100 ms para ambos puertos
  Serial2.setTimeout(100);
}

void loop() {

  if(Serial1.available()){ // Si hay datos en el puerto serial
    if(i < 8){ // Si se han realizado menos de 9 lecturas (el contador inicia en 0)
      cadena = Serial1.readString(); // Leer el string en el puerto serial
      intput = cadena.toInt(); // Convertir a entero la lectura
      lec[i] = intput; // Almacenar la lectura en la posición del array indicada por el contador
      Serial1.println(); 
      Serial1.println("Bit recibido"); // Confirmar la recepción de la información
      if(i == 7){ // Si se han realizado 8 lecturas
        Serial2.write(lec, 8); // Enviar el array de información al otro Arduino
        Serial1.println();
        Serial1.println("Informacion enviada"); // Confirmar el envío de información 
        Serial1.println();
      }

    }
    i++; // Se incrementa el contador 

    if(i == 8){ // Si el contador llega a 8
      i = 0; // Se reinicia
    }
  }

} 

      
      
    


