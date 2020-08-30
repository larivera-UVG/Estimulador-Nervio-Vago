#include <RH_ASK.h>
#include <SPI.h>

//RH_ASK rf_driver;
RH_ASK rf_driver(2000, 9, 11, 0);

String modo, ancho, tiempo, freq, sleep;
String str_out;

int mssg = 0;
int cond1, cond2, cond3, cond4, cond5 = 0;
byte modop[1];
byte anctime[2];
byte freqsleep[2];


void setup() {
  // put your setup code here, to run once:
  rf_driver.init(); // Pin 12 para usar transmisor

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() & cond1 == 0){
    mssg = Serial.read();
    modop[0] = mssg;
    cond1 = 1;
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
  
  if(cond1 == 1 & cond2 == 1 & cond3 == 1 & cond4 == 1 & cond5 == 1){
    cond1 = 0;
    cond2 = 0;
    cond3 = 0;
    cond4 = 0; 
    cond5 = 0;

    /* MODO DE ESTIMULACION */
    if(modop[0] == '1'){
      modo = String(1);
    }
    else if(modop[0] == '2'){
      modo = String(2);
    }
    else if(modop[0] == '3'){
      modo = String(3);
    }

    /* ANCHO DE PULSO */
    if(anctime[0] == '1'){
      ancho = String(1);
    }
    else if(anctime[0] == '2'){
      ancho = String(2);
    }
    else if(anctime[0] == '3'){
      ancho = String(3);
    }
    else if(anctime[0] == '4'){
      ancho = String(4);
    }
    else if(anctime[0] == '5'){
      ancho = String(5);
    }

    /* TIEMPO DE ESTIMULACION */
    if(anctime[1] == '1'){
      tiempo = String(1);
    }
    else if(anctime[1] == '2'){
      tiempo = String(2);
    }
    else if(anctime[1] == '3'){
      tiempo = String(3);
    }
    else if(anctime[1] == '4'){
      tiempo = String(4);
    }
    else if(anctime[1] == '5'){
      tiempo = String(5);
    }
    
    /* FRECUENCIA DE ESTIMULACION */
    if(freqsleep[0] == '1'){
      freq = String(1);
    }
    else if(freqsleep[0] == '2'){
      freq = String(2);
    }
    else if(freqsleep[0] == '3'){
      freq = String(3);
    }
    else if(freqsleep[0] == '4'){
      freq = String(4);
    }
    else if(freqsleep[0] == '5'){
      freq = String(5);
    }
    else if(freqsleep[0] == '6'){
      freq = String(6);
    }
    else if(freqsleep[0] == '7'){
      freq = String(7);
    }
    else if(freqsleep[0] == '8'){
      freq = String(8);
    }

    /* TIEMPO DE SLEEP */
    if(freqsleep[1] == '1'){
      sleep = String(1);
    }
    else if(freqsleep[1] == '2'){
      sleep = String(2);
    }

    str_out = modo + "," + ancho + "," + tiempo + "," + freq + "," + sleep + ",";

    static char *msg = str_out.c_str();

    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
  }
  
}
