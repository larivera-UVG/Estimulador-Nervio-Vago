// Access to Power Managment Register using the structs
// Found in ASF for ATMEL. This code is leveraged with
// the help of video tutorial of Force Tronics in YouTube. 

bool tog = false;
int cDiv = 1;
int count = 0;
#define LED_PIN 1

void setup() {
  PM->CPUSEL.reg = PM_CPUSEL_CPUDIV(1);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  
  if(tog){
    tog = false;
  }
  else{ 
    tog = true; 
  }

  digitalWrite(LED_PIN, tog);
  count++;
  if(count>6)
  {
    if(cDiv == 1) cDiv = 4;
    else cDiv = 1;
    PM->CPUSEL.reg = PM_CPUSEL_CPUDIV(cDiv);
    count = 0;
  }

}
