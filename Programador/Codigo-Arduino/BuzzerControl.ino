/*
    BuzzerControl.ino.
    Archivo que recibe los valores (frecuencias) enviadas desde la interfaz grafica
    de Python, para hacer resonar un buzzer a diferentes frecuencias. 

    Miguel Alfonso Alvarez Sierra - 16168
    Ingeniería Mecatrónica - UVG
*/

/**********************************************************************************
 * VARIABLES DEFINIDAS
 *********************************************************************************/
 
int mssg = 0; // Variable que almacena la lectura de Python
  
void setup()
{
   Serial.begin(9600); // Se inicializa la comunicacion serial con baudrate = 9600
}
  
void loop()
{
   if (Serial.available() > 0) // Si hay datos en el bus serial 
   {
      mssg = Serial.parseInt(); // Se leen los datos del bus serial conviertiendolos a INT
      
      if(mssg == 0){ // Si la lectura es cero
        noTone(8); // Se apaga el buzzer en el pin 8
      }
      else{
        tone(8,mssg); // Se activa el buzzer del pin 8 con la frecuencia recibida 
      }
   }
}
