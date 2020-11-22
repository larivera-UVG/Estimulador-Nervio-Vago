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
    }
    else if(i == 0 & k == 1){
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
    else if(i == 0 & k == 2){
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
    else if(i == 0 & k == 3){
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
    else if(i == 0 & k == 4){
      value = mySwitch.getReceivedValue();
      Serial.print("Tiempo de sleep:  ");
      if(value == 1){
        Serial.println("Sleep 1");
      }
      else if(value == 2){
        Serial.println("Sleep 2");
      }
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
    Serial.println("");
  }
}
