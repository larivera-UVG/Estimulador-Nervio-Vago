int mssg = 0;
int cond1, cond2, cond3, cond4, cond5 = 0;
byte modop[1];
byte anctime[2];
byte freqsleep[2];
byte lec[1];
byte lec2[2];
byte lec3[2];

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  
  Serial1.begin(115200);
  Serial2.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial1.available() & cond1 == 0){
    mssg = Serial1.read();
    modop[0] = mssg;
    cond1 = 1;
    Serial1.println("Recibido");
  }
  if(Serial1.available() & cond1 == 1 & cond2 == 0){
    mssg = Serial1.read();
    anctime[0] = mssg;
    cond2 = 1;
    Serial1.println("Recibido");
  }
  if(Serial1.available() & cond1 == 1 & cond2 == 1 & cond3 == 0){
    mssg = Serial1.read();
    anctime[1] = mssg;
    cond3 = 1;
    Serial1.println("Recibido");
  }
  if(Serial1.available() & cond1 == 1 & cond2 == 1 & cond3 == 1 & cond4 == 0){
    mssg = Serial1.read();
    freqsleep[0] = mssg;
    cond4 = 1;
    Serial1.println("Recibido");
  }
  if(Serial1.available() & cond1 == 1 & cond2 == 1 & cond3 == 1 & cond4 == 1 & cond5 == 0){
    mssg = Serial1.read();
    freqsleep[1] = mssg;
    cond5 = 1;
    Serial1.println("Recibido");
  }

  if(cond1 == 1 & cond2 == 1 & cond3 == 1 & cond4 == 1 & cond5 == 1){
    cond1 = 0;
    cond2 = 0;
    cond3 = 0;
    cond4 = 0; 
    cond5 = 0;

    /* MODO DE ESTIMULACION */
    if(modop[0] == '1'){
      lec[0] = 1;
    }
    else if(modop[0] == '2'){
      lec[0] = 2;
    }
    else if(modop[0] == '3'){
      lec[0] = 3;
    }

    /* ANCHO DE PULSO */
    if(anctime[0] == '1'){
      lec2[0] = 0;
    }
    else if(anctime[0] == '2'){
      lec2[0] = 01;
    }
    else if(anctime[0] == '3'){
      lec2[0] = 10;
    }
    else if(anctime[0] == '4'){
      lec2[0] = 11;
    }
    else if(anctime[0] == '5'){
      lec2[0] = 100;
    }

    /* TIEMPO DE ESTIMULACION */
    if(anctime[1] == '1'){
      lec2[1] = 0;
    }
    else if(anctime[1] == '2'){
      lec2[1] = 01;
    }
    else if(anctime[1] == '3'){
      lec2[1] = 10;
    }
    else if(anctime[1] == '4'){
      lec2[1] = 11;
    }
    else if(anctime[1] == '5'){
      lec2[1] = 100;
    }
    
    /* FRECUENCIA DE ESTIMULACION */
    if(freqsleep[0] == '1'){
      lec3[0] = 0;
    }
    else if(freqsleep[0] == '2'){
      lec3[0] = 01;
    }
    else if(freqsleep[0] == '3'){
      lec3[0] = 10;
    }
    else if(freqsleep[0] == '4'){
      lec3[0] = 11;
    }
    else if(freqsleep[0] == '5'){
      lec3[0] = 100;
    }
    else if(freqsleep[0] == '6'){
      lec3[0] = 101;
    }
    else if(freqsleep[0] == '7'){
      lec3[0] = 110;
    }
    else if(freqsleep[0] == '8'){
      lec3[0] = 111;
    }

    if(freqsleep[1] == '1'){
      lec3[1] = 0;
    }
    else if(freqsleep[1] == '2'){
      lec3[1] = 01;
    }

    int i = 0;
    while(i <= 2){
      if(i == 0){
        Serial2.write(lec,1);
      }
      else if(i == 1){
        Serial2.write(lec2,2);
      }
      else if(i == 2){
        Serial2.write(lec3,2);
      }
      i++;
    }
    
  }


}

    
    

