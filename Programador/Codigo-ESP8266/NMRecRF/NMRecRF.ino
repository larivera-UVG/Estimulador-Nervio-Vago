/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int i = 0; 
int k = 0;
int value; 
int slcond = 0; 

void setup() {
  Serial.begin(115200);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {

    if(i == 0 & k == 0){
      value = mySwitch.getReceivedValue();
      Serial.print("Modo: ");
      if(value == 1){
        Serial.println("Estimulación");
      }
      else if(value == 2){
        Serial.println("Iman");
      }
      else if(value == 3){
        Serial.println("Reposo");
      }
      //Serial.print("Modo:  ");
      //Serial.println( value );
      //Serial.println("");
    }
    else if(i == 0 & k == 1){
      value = mySwitch.getReceivedValue();
      Serial.print("Ancho de pulso:  ");
      Serial.println( value );
      //cond2
      //Serial.println("");
    }
    else if(i == 0 & k == 2){
      value = mySwitch.getReceivedValue();
      Serial.print("Tiempo de estimulación:  ");
      Serial.println( value );
      //Serial.println("");
    }
    else if(i == 0 & k == 3){
      value = mySwitch.getReceivedValue();
      Serial.print("Frecuencia:  ");
      Serial.println( value );
     // Serial.println("");
    }
    else if(i == 0 & k == 4){
      value = mySwitch.getReceivedValue();
      Serial.print("Tiempo de sleep:  ");
      Serial.println( value );
      //Serial.println("");
    }
    else if(i == 5 & k == 4){
      slcond = 1; 
    }

    mySwitch.resetAvailable();
    i++;
    
  }

  
  if(i == 4 & k == 0){
    i = 0;
    k = 1;
  }
  else if(i == 5 & k == 1){
    i = 0;
    k = 2;
  }
  else if(i == 5 & k == 2){
    i = 0;
    k = 3;
  }
  else if(i == 5 & k == 3){
    i = 0;
    k = 4;
  }
  else if(i == 5 & k == 4){
    i = 0;
    k = 5;
    slcond = 0;
  }

  if(k == 5){
    k = 0;
  }
}
