/* ReadTry.ino - PROGRAMA DE LECTURA DE INFORMACION RECIBIDA DESDE OTRO ARDUINO 
 *  Miguel Alvarez - 16168
 */

byte msg1[0]; // Array para almacenamiento de primera lectura
byte msg2[2]; // Array para almacenamiento de primera lectura
byte msg3[2]; // Array para almacenamiento de primera lectura
int cond1, cond2, cond3 = 0; // Variables de condiciones 
int p10, p11, p12, p13, p14, p15, p16, p17; // Enteros para separar el array de la primera lectura
int p20, p21, p22, p23, p24, p25, p26, p27; // Enteros para separar el array de la primera lectura
int p30, p31, p32, p33, p34, p35, p36, p37; // Enteros para separar el array de la primera lectura

void setup() {
  Serial1.begin(9600); // Inicialización del primer puerto serial 
  Serial2.begin(9600); // Inicialización del primer puerto serial 

  Serial1.setTimeout(100); // Timeout de 100 ms
  Serial2.setTimeout(100); // Timeout de 100 ms

  pinMode(9, OUTPUT); 
  pinMode(11, OUTPUT); // Se define el pin 11 como salida
  pinMode(3, OUTPUT);
}

void loop() {

  // PRIMER BYTE
  if(Serial1.available() & cond1 == 0){ // Si hay datos en el puerto serial 1 y la condición 1 es 0
    Serial1.readBytes(msg1, 1); // Lectura del array recibido
    p10 = msg1[0]; // Se actualizan los enteros de almacenamiento
    cond1 = 1; // Se activa la condición 1
  }

  // SEGUNDO BYTE
  if(Serial1.available() & cond1 == 1 & cond2 == 0){ // Si hay datos en el puerto serial 1 y la condición 1 es 1 y la 2 es 0
    Serial1.readBytes(msg2, 2);
    p20 = msg2[0];
    p21 = msg2[1];
    cond2 = 1; // Se activa la condición 2
  }

  // TERCER BYTE
  if(Serial1.available() & cond1 == 1 & cond2 == 1 & cond3 == 0){ // Si hay datos en el puerto serial 1 y la condición 1 es 1 y la 2 es 1 y la 3 es 0
    Serial1.readBytes(msg3, 2);
    p30 = msg3[0];
    p31 = msg3[1];
    cond3 = 1; // Se activa la condición 3
  }
  
  if(cond1 == 1 & cond2 == 1 & cond3 == 1){ // Al cumplirse las tres condiciones

    cond1 = 0; // Se reinician las tres condiciones
    cond2 = 0; 
    cond3 = 0;

    /* MODO DE OPERACION */
    if(p10 == 1){
      Serial2.println("Modo 1");
    }
    else if(p10 == 2){
      Serial2.println("Modo 2");
    }
    else if(p10 == 3){
      Serial2.println("Modo 3");
    }

    /* MODIFICACION DEL ANCHO DE PULSO */
    if(p20 == 0){
      analogWrite(11, 64);
      analogWrite(9, 64);
      analogWrite(3, 64);
      Serial2.println("Ancho 25%");
    }
    else if(p20 == 01){ 
      analogWrite(11, 77);
      analogWrite(9, 77);
      analogWrite(3, 77);
      Serial2.println("Ancho 30%");
    }
    else if(p20 == 10){
      analogWrite(11, 127);
      analogWrite(9, 127);
      analogWrite(3, 127);
      Serial2.println("Ancho 50%");
    }
    else if(p20 == 11){
      analogWrite(11, 192);
      analogWrite(9, 192);
      analogWrite(3, 192);
      Serial2.println("Ancho 75%");
    }
    else if(p20 == 100){
      analogWrite(11, 255);
      analogWrite(9, 255);
      analogWrite(3, 255);
      Serial2.println("Ancho 100%");
    }
    

    /* MODIFICACION DEL TIEMPO DE ESTIMULACION */
    if(p21 == 0){
      Serial2.println("Tiempo 1");
    }
    else if(p21 == 01){
      Serial2.println("Tiempo 2");
    }
    else if(p21 == 10){
      Serial2.println("Tiempo 3");
    }
    else if(p21 == 11){
      Serial2.println("Tiempo 4");
    }
    else if(p21 == 100){
      Serial2.println("Tiempo 5");
    }

    TCCR1B = TCCR1B & B11111000 | B00000011; // Frecuencia de 490.20 Hz en Pin 
    TCCR1B = TCCR1B & B11111000 | B00000011; 

    TCCR3B = TCCR3B & B11111000 | B00000011;    // set timer 3 divisor to    64 for PWM frequency of   490.20 Hz
    /* MODIFICACION DE LA FRECUENCIA */
    if(p30 == 0){
      TCCR2B = TCCR2B & B11111000 | B00000100; // Frecuencia de 490.20 Hz en Pin 9/10
      //TCCR2B = TCCR2B & B11111000 | B00000100;
      Serial2.println("Frecuencia: 490.20 Hz");
    }
    else if(p30 == 01){
      TCCR2B = TCCR2B & B11111000 | B00000111; // Frecuencia de 30.64 Hz en Pin 9/10
      Serial2.println("Frecuencia: 30.64 Hz");
    }
    else if(p30 == 10){
      TCCR2B = TCCR2B & B11111000 | B00000110; // Frecuencia de 122.50 Hz en Pin 9/10
      Serial2.println("Frecuencia: 122.50 Hz");
    }
    else if(p30 == 11){
      TCCR2B = TCCR2B & B11111000 | B00000101; // Frecuencia de 245.10 Hz en Pin 9/10
      Serial2.println("Frecuencia: 245.10 Hz");
    }
    else if(p30 == 100){
      TCCR2B = TCCR2B & B11111000 | B00000011; // Frecuencia de 980.39 Hz en Pin 9/10
      // CUAL ES EL VERDADERO 490.20? 
      Serial2.println("Frecuencia: 980.39 Hz");
    }
    else if(p30 == 101){
      TCCR2B = TCCR2B & B11111000 | B00000010; // Frecuencia de 3921.16 Hz en Pin 9/10
      Serial2.println("Frecuencia: 3921.16 Hz");
    }
    else if(p30 == 110){
      TCCR2B = TCCR2B & B11111000 | B00000001; // Frecuencia de 31372.55 Hz en Pin 9/10
      Serial2.println("Frecuencia: 31372.55 Hz");
    }
    else if(p30 == 111){
      Serial2.println("Frecuencia 8");
    }

    
   
  }
    


}
