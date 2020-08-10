/* ReadTry.ino - PROGRAMA DE LECTURA DE INFORMACION RECIBIDA DESDE OTRO ARDUINO 
 *  Miguel Alvarez - 16168
 */

byte msg1[8]; // Array para almacenamiento de primera lectura
byte msg2[8]; // Array para almacenamiento de primera lectura
byte msg3[8]; // Array para almacenamiento de primera lectura
int cond1, cond2, cond3 = 0; // Variables de condiciones 
int p10, p11, p12, p13, p14, p15, p16, p17; // Enteros para separar el array de la primera lectura
int p20, p21, p22, p23, p24, p25, p26, p27; // Enteros para separar el array de la primera lectura
int p30, p31, p32, p33, p34, p35, p36, p37; // Enteros para separar el array de la primera lectura

void setup() {
  Serial1.begin(9600); // Inicialización del primer puerto serial 
  Serial2.begin(9600); // Inicialización del primer puerto serial 

  Serial1.setTimeout(100); // Timeout de 100 ms
  Serial2.setTimeout(100); // Timeout de 100 ms

  pinMode(11, OUTPUT); // Se define el pin 11 como salida
}

void loop() {

  // PRIMER BYTE
  if(Serial1.available() & cond1 == 0){ // Si hay datos en el puerto serial 1 y la condición 1 es 0
    Serial1.readBytes(msg1, 8); // Lectura del array recibido
    p10 = msg1[0]; // Se actualizan los enteros de almacenamiento
    p11 = msg1[1];
    p12 = msg1[2];
    p13 = msg1[3];
    p14 = msg1[4];
    p15 = msg1[5];
    p16 = msg1[6];
    p17 = msg1[7];
    cond1 = 1; // Se activa la condición 1
  }

  // SEGUNDO BYTE
  if(Serial1.available() & cond1 == 1 & cond2 == 0){ // Si hay datos en el puerto serial 1 y la condición 1 es 1 y la 2 es 0
    Serial1.readBytes(msg2, 8);
    p20 = msg2[0];
    p21 = msg2[1];
    p22 = msg2[2];
    p23 = msg2[3];
    p24 = msg2[4];
    p25 = msg2[5];
    p26 = msg2[6];
    p27 = msg2[7];
    cond2 = 1; // Se activa la condición 2
  }

  // TERCER BYTE
  if(Serial1.available() & cond1 == 1 & cond2 == 1 & cond3 == 0){ // Si hay datos en el puerto serial 1 y la condición 1 es 1 y la 2 es 1 y la 3 es 0
    Serial1.readBytes(msg3, 8);
    p30 = msg3[0];
    p31 = msg3[1];
    p32 = msg3[2];
    p33 = msg3[3];
    p34 = msg3[4];
    p35 = msg3[5];
    p36 = msg3[6];
    p37 = msg3[7];
    cond3 = 1; // Se activa la condición 3
  }
  
  if(cond1 == 1 & cond2 == 1 & cond3 == 1){ // Al cumplirse las tres condiciones

    cond1 = 0; // Se reinician las tres condiciones
    cond2 = 0; 
    cond3 = 0;

    /* MODIFICACION DEL ANCHO DE PULSO */
    if(p26 == 0 & p25 == 0 & p24 == 0){
      analogWrite(11, 64);
      Serial2.println("Ancho 25%");
    }
    else if(p26 == 0 & p25 == 0 & p24 == 1){
      analogWrite(11, 127);
      Serial2.println("Ancho 50%");
    }
    else if(p26 == 0 & p25 == 1 & p24 == 0){
      analogWrite(11, 192);
      Serial2.println("Ancho 75%");
    }
    else if(p26 == 0 & p25 == 1 & p24 == 1){
      analogWrite(11, 255);
      Serial2.println("Ancho 100%");
    }
    else if(p26 == 1 & p25 == 0 & p24 == 0) Serial2.println("Ancho 5");

    /* MODIFICACION DEL TIEMPO DE ESTIMULACION */
    if(p22 == 0 & p21 == 0 & p20 == 0) Serial2.println("Tiempo 1");
    else if(p22 == 0 & p21 == 0 & p20 == 1) Serial2.println("Tiempo 2");
    else if(p22 == 0 & p21 == 1 & p20 == 0) Serial2.println("Tiempo 3");
    else if(p22 == 0 & p21 == 1 & p20 == 1) Serial2.println("Tiempo 4");
    else if(p22 == 1 & p21 == 0 & p20 == 0) Serial2.println("Tiempo 5");
    else if(p22 == 1 & p21 == 0 & p20 == 1) Serial2.println("Tiempo 6");
    else if(p22 == 1 & p21 == 1 & p20 == 0) Serial2.println("Tiempo 7");
    else if(p22 == 1 & p21 == 1 & p20 == 1) Serial2.println("Tiempo 8");

    /* MODIFICACION DE LA FRECUENCIA */
    if(p37 == 0 & p36 == 0 & p35 == 0){
      TCCR2B = TCCR2B & B11111000 | B00000100; // Frecuencia de 490.20 Hz en Pin 3/11
      Serial2.println("Frecuencia 1");
    }
    else if(p37 == 0 & p36 == 0 & p35 == 1){
      TCCR2B = TCCR2B & B11111000 | B00000111; // Frecuencia de 30.64 Hz en Pin 3/11
      Serial2.println("Frecuencia 2");
    }
    else if(p37 == 0 & p36 == 1 & p35 == 0) Serial2.println("Frecuencia 3");
    else if(p37 == 0 & p36 == 1 & p35 == 1) Serial2.println("Frecuencia 4");
    else if(p37 == 1 & p36 == 0 & p35 == 0) Serial2.println("Frecuencia 5");
    else if(p37 == 1 & p36 == 0 & p35 == 1) Serial2.println("Frecuencia 6");
    else if(p37 == 1 & p36 == 1 & p35 == 0) Serial2.println("Frecuencia 7");
    else if(p37 == 1 & p36 == 1 & p35 == 1) Serial2.println("Frecuencia 8");
      
   
  }
    


}
