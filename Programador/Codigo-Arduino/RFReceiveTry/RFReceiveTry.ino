#include <RH_ASK.h>
#include <SPI.h> 

RH_ASK rf_driver(2000, 9, 11, 0);

String str_out;
String modo, ancho, tiempo, freq, sleep;
int cont = 0;
int lastIndex = 0;
String par[5];


void setup() {
  // put your setup code here, to run once:

   

  rf_driver.init(); // Pin 9 para receptor 
  Serial.begin(115200);

  pinMode(5, OUTPUT);

  

}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t buf[10];
  uint8_t buflen = sizeof(buf);

  if(rf_driver.recv(buf, &buflen)){

    
    str_out = String((char*)buf);

    

    for(int i = 0; i < str_out.length(); i++){
      if (str_out.substring(i, i+1) == ",") {
          // Grab the piece from the last index up to the current position and store it
          par[cont] = str_out.substring(lastIndex, i);
          // Update the last position and add 1, so it starts from the next character
          lastIndex = i + 1;
          // Increase the position in the array that we store into
          cont++;
        }

        // If we're at the end of the string (no more commas to stop us)
        if (i == str_out.length() - 1) {
          // Grab the last part of the string from the lastIndex to the end
          par[cont] = str_out.substring(lastIndex, i);
        }
      }
      

      // Clear out string and counters to get ready for the next incoming string
      cont = 0;
      lastIndex = 0;
       
    if(par[0] == "1"){
      Serial.println("Modo 1"); 
    }
    else if(par[0] == "2"){
      Serial.println("Modo 2");
    }
    else if(par[0] == "3"){
      Serial.println("Modo 3");
    }

    if(par[1] == "1"){
      //analogWrite(5, 64);
      Serial.println("Ancho 25%"); 
    }
    else if(par[1] == "2"){
      //analogWrite(3, 77);
      Serial.println("Ancho 30%");
    }
    else if(par[1] == "3"){
      //analogWrite(3, 127);
      Serial.println("Ancho 50%");
    }
    else if(par[1] == "4"){
      //analogWrite(3, 192);
      Serial.println("Ancho 75%");
    }
    else if(par[1] == "5"){
      //analogWrite(3,255); 
      Serial.println("Ancho 100%");
    }

    if(par[2] == "1"){
      Serial.println("Tiempo 1"); 
    }
    else if(par[2] == "2"){
      Serial.println("Tiempo 2");
    }
    else if(par[2] == "3"){
      Serial.println("Tiempo 3");
    }
    else if(par[2] == "4"){
      Serial.println("Tiempo 4");
    }
    else if(par[2] == "5"){
      Serial.println("Tiempo 5");
    }

    if(par[3] == "1"){
      TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)
      Serial.println("490.20 Hz"); 
    }
    else if(par[3] == "2"){
      TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz
      Serial.println("30.64 Hz");
    }
    else if(par[3] == "3"){
      TCCR2B = TCCR2B & B11111000 | B00000110; // for PWM frequency of 122.55 Hz
      Serial.println("122.50 Hz");
    }
    else if(par[3] == "4"){
      TCCR2B = TCCR2B & B11111000 | B00000101; // for PWM frequency of 245.10 Hz
      Serial.println("245.10 Hz");
    }
    else if(par[3] == "5"){
      TCCR2B = TCCR2B & B11111000 | B00000011; // for PWM frequency of 980.39 Hz
      Serial.println("980.39 Hz");
    }
    else if(par[3] == "6"){
      TCCR2B = TCCR2B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
      Serial.println("3921.16 Hz");   
    }
    else if(par[3] == "7"){
      TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
      Serial.println("31372.55 Hz");
    }
    else if(par[3] == "8"){
      Serial.println("Frecuencia 8");
    }

    if(par[4] == "1"){
      Serial.println("Sleep 1"); 
    }
    else if(par[4] == "2"){
      Serial.println("Sleep 2");
    }

    Serial.println("");


  }

}
