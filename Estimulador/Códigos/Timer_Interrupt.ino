/*
This sketch illustrates how to set a timer on an SAMD21 based board in Arduino (Feather M0, Arduino Zero should work)
It should generate a 1Hz square wave as it is (thanks richdrich for the suggestion)
*/

uint32_t sampleRate = 1000;//7692300;      //sample rate in milliseconds, determines how often TC5_Handler is called (in mili-Hertz)
#define LED_PIN 0                   //Output pin for PWM
bool state = 0;                     //just for an example


void setup() {
  pinMode(LED_PIN,OUTPUT);          //configures the LED pin as output
  
  tcConfigure(sampleRate);          //configure the timer to run at <sampleRate>Hertz
  tcStartCounter();                 //starts the timer
}


void loop() {
  //tcDisable();                    //This function can be used anywhere if you need to stop/pause the timer
  //tcReset();                      //This function should be called everytime you stop the timer
}


//this function gets called by the interrupt at <sampleRate>Hertz
void TC5_Handler (void) {
  
  //**************** YOUR CODE HERE **************
  if(state == true) {
    digitalWrite(LED_PIN,HIGH);
  } else {
    digitalWrite(LED_PIN,LOW);
  }
  state = !state;
  //************** END OF YOUR CODE **************
  
  TC5->COUNT16.INTFLAG.bit.MC0 = 1; //Writing a 1 to INTFLAG.bit.MC0 clears the interrupt so that it will run again
}


//Configures the TC to generate output events at the sample frequency.
//Configures the TC in Frequency Generation mode, with an event output once
//each time the audio sample frequency period expires.

 void tcConfigure(int sampleRate)
{
    
  // Enable GCLK0 and connect it to TC4 and TC5
  GCLK->CLKCTRL.reg = (uint16_t)(GCLK_CLKCTRL_CLKEN | 
                                GCLK_CLKCTRL_GEN_GCLK0 | 
                                GCLK_CLKCTRL_ID(GCM_TC4_TC5)) ;
  while (GCLK->STATUS.bit.SYNCBUSY);
  tcReset(); //reset TC5

  // Set TC5 Mode, WaveForm, Prescaler and Enable it 
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;                         // Set Timer counter Mode to 16 bits
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;                         // Set TC5 mode as match frequency
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024 | TC_CTRLA_ENABLE;  // Set prescaler and enable TC5
  TC5->COUNT16.CC[0].reg = (uint16_t) (SystemCoreClock / sampleRate - 1);  // Set TC5 timer counter based off of the system clock and the user defined sample rate or waveform
  while (tcIsSyncing());
  
  // Configure interrupt request
  NVIC_DisableIRQ(TC5_IRQn);
  NVIC_ClearPendingIRQ(TC5_IRQn);
  NVIC_SetPriority(TC5_IRQn, 0);
  NVIC_EnableIRQ(TC5_IRQn);
  
  TC5->COUNT16.INTENSET.bit.MC0 = 1;           // Enable the TC5 interrupt request
  while (tcIsSyncing());                       // Wait until TC5 is done syncing 
} 


//Function that is used to check if TC5 is done syncing
//returns true when it is done syncing
bool tcIsSyncing()
{
  return TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY;
}


//This function enables TC5 and waits for it to be ready
void tcStartCounter()
{
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE; //set the CTRLA register
  while (tcIsSyncing()); //wait until snyc'd
}


void tcReset()
{
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (tcIsSyncing());
  while (TC5->COUNT16.CTRLA.bit.SWRST);
}


void tcDisable()
{
  TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (tcIsSyncing());
}
