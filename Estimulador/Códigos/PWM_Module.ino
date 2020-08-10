 
// ............................................. PWM and Timer Formulas ................................................

// PWM frequency:
// freq = GCLKx_freq/(TCCx_Prescaler*(1+TOP_Value))
// => Top_Value = (GCLKx_freq/TCCx_Prescaler*freq)-1

// Timer value:
// Time = (Timer_Presc*dfactor/GCLKx_freq)*(CCx+1)
// => CCx = time*(GCLKx_freq/Timer_Presc*dfactor)-1

// Note: dfactor is a scaling factor selected in clock divider to GCLKx configuration


// ....................................... PWM and Timer Values Data Base...............................................


// Frequency configuration of the Stimulation Signal (PWM) for 30, 25, 20, 15, 10, 5, 2 and 1Hz  
const unsigned int PWM_freq[3][8] = {{1562, 1874, 2343, 3124, 4687, 9374, 23437, 46874},    // 48MHz
                                     {2082, 2499, 3124, 4166, 6249, 12499, 31249, 62499},   // 8MHz
                                     {1066, 1279, 1599, 2132, 3199, 6399, 15999, 31999}};   // 32KHz

// CCx values for 1ms, 750us, 500us, 250us and 130us respectively, for pulse 
// width or hight state in the square signal (PWM) during the Stimulation Time
const unsigned char PWM_pw[3][5] = {{47, 35, 23, 12, 6},   // 48MHz
                                    {62, 47, 31, 16, 8},   // 8MHz
                                    {32, 24, 16, 8, 4}};   // 32KHz

// Array for CCx values for 600, 300, 180, 108, 66, 60 48, 30, 21, 18, 14, 7, 2, 1s respectively, for
// On/Off time for Stimulation Signal. Clock at 32KHz
const unsigned int ON_OFF_TIME[14] = {18749, 9374, 5624, 3374, 2062, 1874, 1499, 937, 655, 562, 437, 218, 62, 30};


// ........................................ PWM and Timer Values Selection .............................................


volatile unsigned int period = PWM_freq[0][4];
volatile float pulse_width = period*0.5; //PWM_pw[2][4];       
volatile int ON_Time = ON_OFF_TIME[13];
volatile int OFF_Time = ON_OFF_TIME[13];


// ............................... Variables for PWM, Timer and Digital Potentiometer ..................................


bool state = 0;

// Select Gen Clock to setting the waveform generator clock or sample rate
const unsigned char gClock = 4;

// Set the divide factor for the Gen Clock, 48MHz/1 = 48MHz
const unsigned char dFactor = 1; 

const int UD = 1;
const int INC = 2;
const int CS = 3;

bool flag=0;
byte mode=0;
int amplitude=1;
int pulsos=0;

// .....................................................................................................................


void setup()
{

//...................................... Set Input/Output Pins Mode Configuration ......................................
  
  pinMode(0, OUTPUT);               // VNS Stimulation Signal Output
  pinMode(UD, OUTPUT);              // U/'D
  pinMode(INC, OUTPUT);             // 'INC
  pinMode(CS, OUTPUT);              // 'CS
  //analogWriteResolution(10);
  digitalWrite(UD, HIGH);
  digitalWrite(INC, HIGH);
  digitalWrite(CS, HIGH);  
 
  setResistance(0);

//...................................... Configurare PWM (Stimulation signal) ..........................................

  PWM_Config();
  Enable_PWM_Interrupts();  
  //PWM_Start();

//...................................... Configurar Timer (ON/OFF Time) ................................................

  Timer_Config();           
  Timer_Start();    

// .....................................................................................................................

  //DAC_Init(); 
  flag=1;

}


// .....................................................................................................................


void loop() 
{

  if(flag==1)
  {
     
    switch (amplitude) 
    { 
      case 0:
        setResistance(0);      
        break;
      case 1:
        setResistance(8);
        break;       
      case 2:
        setResistance(15);
        break;       
      case 3:
        setResistance(23);
        break;
      case 4:
        setResistance(30);
        break;
      case 5:
        setResistance(38);
        break;
      case 6:
        setResistance(45);
        break; 
      case 7:
        setResistance(53);
        break; 
      case 8:
        setResistance(61);
        break;          
      case 9:
        setResistance(68);
        break;  
      case 10:
        setResistance(76);
        break; 
      case 11:
        setResistance(83);
        break;
      case 12:
        setResistance(91);
        break;
      case 13:
        setResistance(98);
        break;                                          
      default:
        setResistance(98);
        break;
    }
    flag=0;
  }
}


// .....................................................................................................................


void TCC0_Handler()
{

  if(mode==1)
  {
    amplitude++;     
    if(amplitude>11) amplitude=11;    
    flag=1;  
  } 
  else if(mode==3)
  {
    amplitude--;     
    if(amplitude<1) amplitude=1;    
    flag=1;     
  }
  else
  {
    //amplitude=10;
    //flag=1;  
  }
  
  TCC0->INTFLAG.bit.MC0 = 1;                            // Clear interrupt flag
}


// .....................................................................................................................


//void enable_interrupts() 
//{
//  NVIC_SetPriority(TCC1_IRQn, 0);
//  NVIC_EnableIRQ(TCC1_IRQn);   
//}
//
//
//void TCC1_Handler() {
//  REG_TCC1_PER = 128;
//  while (TCC1->SYNCBUSY.bit.PER);
//
//  REG_TCC1_CC1 = (208/255.0)*128;
//  while (TCC1->SYNCBUSY.bit.CC1);
//
//  REG_TCC0_INTFLAG = TC_INTFLAG_OVF;
//
//}


// .....................................................................................................................


void setResistance(int percent){ 
  digitalWrite(UD, LOW);                // Select Decrement Counter
  digitalWrite(CS, LOW);                // Select Digital Potenciometer
    
  for (int i=0; i<100; i++){            // Increment/Decrement Counter
    digitalWrite(INC, LOW);             // Low State (this gives a negative edge)
    delayMicroseconds(10);               
    digitalWrite(INC, HIGH);            // High State 
    delayMicroseconds(10);
  }

  digitalWrite(UD, HIGH);               // Select Increment Counter
  for (int i=0; i<percent; i++){        // Increment/Decrement Counter
    digitalWrite(INC, LOW);             // Low State (this gives a negative edge)
    delayMicroseconds(10);
    digitalWrite(INC, HIGH);            // High State 
    delayMicroseconds(10);
  }

  //digitalWrite(CS, HIGH);               // Save counter in non-volatile memory and enter in Stand-By Mode
}


// .....................................................................................................................


void TC5_Handler (void) {

  mode++;                                               // Ramp Up -> ON Time -> Ramp Down -> OFF Time
  if(mode>=5) mode=1;                                   // Reset Stimultation Sequence

  if(mode == 1)
  {
    flag=1;
    Timer_Disable();                                    // Stop Timer to change to Ramp Up Time
    TC5->COUNT16.CC[0].reg = (uint16_t) OFF_Time;       // Set TC5 value with Ramp Up Time    
    PWM_Start(); 
    Timer_Start();                                      // Enable Timer again    
  }
  else if(mode == 2)
  {
    Timer_Disable();                                    // Stop Timer to change to ON time value       
    TC5->COUNT16.CC[0].reg = (uint16_t) ON_Time;        // Set TC5 value with ON Time (Stimulation)
    //PWM_Start();                                        // Enable PWM 
    Timer_Start();                                      // Enable Timer again     
  } 
  else if(mode == 3) 
  {    
    amplitude--;
    flag=1;
    Timer_Disable();                                    // Stop Timer to change to Ramp Down Time
    TC5->COUNT16.CC[0].reg = (uint16_t) OFF_Time;       // Set TC5 value with Ramp Down Time    
    Timer_Start();                                      // Enable Timer again                   
  }
  else if(mode == 4)
  {
    PWM_Stop();                                         // Disable PWM     
    Timer_Disable();                                    // Stop Timer to change to OFF Time Value
    TC5->COUNT16.CC[0].reg = (uint16_t) OFF_Time;       // Set TC5 value with OFF Time (Repose)    
    Timer_Start();                                      // Enable Timer again    
    //digitalWrite(0, LOW);     
  }
       
  TC5->COUNT16.INTFLAG.bit.MC0 = 1;                     // Clear interrupt flag  
}


// .....................................................................................................................


void PWM_Config()
{

  // Enable and configure the Generic CLK Generator (GCLK)
  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |                   // Improve duty cycle 
                     GCLK_GENCTRL_GENEN |                 // Enable GCLK
                     GCLK_GENCTRL_SRC_DFLL48M |           // OSC32K | OSC8M | DFLL48M |   // Set the 48MHz as Clock Source
                     GCLK_GENCTRL_ID(gClock);             // Select GCLK4 as ID 
  while (GCLK->STATUS.bit.SYNCBUSY);                      // Wait for synchronization

  // Select clock divider to GCLK4
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |                  // Divide 48MHz by 1 
                    GCLK_GENDIV_ID(gClock);               // Apply it to GCLK4    
  while (GCLK->STATUS.bit.SYNCBUSY);                      // Wait for synchronization
  
  // Enable GCLK4 and connect it to TCC0 and TCC1
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |                 // Enable Generic Clock 
                     GCLK_CLKCTRL_GEN_GCLK4 |             // Select GCLK4
                     GCLK_CLKCTRL_ID_TCC0_TCC1;           // Feed CLK4 to TCC0 and TCC1
  while (GCLK->STATUS.bit.SYNCBUSY);                      // Wait for synchronization

  TCC0->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV1024;         // Divide counter by 1 (This is N)
  TCC0->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;               // Set Timer counter Mode to 16 bits
  TCC0->WAVE.reg = TCC_WAVE_WAVEGEN_NPWM;                 // Select NPWM (Single-slope): count up to PER, match on CC[n]
  while (TCC0->SYNCBUSY.bit.WAVE);                        // Wait for synchronization

  TCC0->PER.reg = period;                                 // Set the period (TOP) for rate or frequency of PWM signal
  while (TCC0->SYNCBUSY.bit.PER);                         // Wait for synchronization

  // Set duty cycle where n for CC[n] is n = x % 4 and x is form WO[x]
  TCC0->CC[0].reg = pulse_width;                          // Set PWM signal to 50% of duty cicle 
  while (TCC0->SYNCBUSY.bit.CC0);                         // Wait for synchronization

  // Configure PA08 (D0 in Trinket) to be output
  PORT->Group[PORTA].DIRSET.reg = PORT_PA08;              // Set pin as output
  PORT->Group[PORTA].OUTCLR.reg = PORT_PA08;              // Set pin to low
  PORT->Group[PORTA].PINCFG[8].reg |= PORT_PINCFG_PMUXEN; // Enable the port multiplexer for PA08

  // Connet TCC1 timer to PA08. Function F is TCC1/WO[2] for PA08. Function E is TCC0/WO[0]
  // Odd pin num (2*n+1): use PMUXO
  // Even pin num (2*n): use PMUXE
  PORT->Group[PORTA].PMUX[4].reg = PORT_PMUX_PMUXE_E;

//  REG_TCC1_INTENSET = TCC_INTENSET_OVF;
//  enable_interrupts();
  
}


// .....................................................................................................................


void Enable_PWM_Interrupts(void)
{
  // Configure interrupt request
  NVIC_DisableIRQ(TCC0_IRQn);                           // Deshabilitar interrupciones
  NVIC_ClearPendingIRQ(TCC0_IRQn);                      // Limpiar banderas de interrupción
  NVIC_SetPriority(TCC0_IRQn, 0);                       // Nivel de prioridad de la interrupción
  NVIC_EnableIRQ(TCC0_IRQn);                            // Habilitar interrupciones
  
  TCC0->INTENSET.bit.MC0 = 1;                           // Enable TC5 Overflow Interrupt Request (OVF)
  while(TCC0->STATUS.reg & TC_STATUS_SYNCBUSY); 
}


// .....................................................................................................................


void PWM_Start()
{ 
  TCC0->CTRLA.reg |= (TCC_CTRLA_ENABLE);              // Enable TCC1 (Start PWM)
  while (TCC0->SYNCBUSY.bit.ENABLE);                  // Wait for synchronization     
}


// .....................................................................................................................


void PWM_Stop()
{
  TCC0->CTRLA.reg &= (~TCC_CTRLA_ENABLE);             // Disable TCC1 (Stop PWM)
  while (TCC0->SYNCBUSY.bit.ENABLE);                  // Wait for synchronization
}


// .....................................................................................................................


void Timer_Config()
{

  // Enable and configure the Generic CLK Generator (GCLK)
  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |                 // Improve duty cycle 
                     GCLK_GENCTRL_GENEN |               // Enable GCLK
                     GCLK_GENCTRL_SRC_OSC32K |          // Set the 32KHz as Clock Source
                     GCLK_GENCTRL_ID(5);                // Select GCLK5 as ID 
  while (GCLK->STATUS.bit.SYNCBUSY);                    // Wait for synchronization

  // Select clock divider to GCLK5
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |                // Divide 32KHz by 1
                    GCLK_GENDIV_ID(5);                  // Apply it to GCLK5 
  while (GCLK->STATUS.bit.SYNCBUSY);                    // Wait for synchronization

  // Enable GCLK0 and connect it to TC4 and TC5
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |               // Enable Generic Clock 
                     GCLK_CLKCTRL_GEN_GCLK5 |           // Select GCLK5
                     GCLK_CLKCTRL_ID_TC4_TC5;           // Feed CLK5 to TC4 and TC5
  while (GCLK->STATUS.bit.SYNCBUSY);                    // Wait for synchronization
 
  Timer_Reset(); //reset TC5

  // Set TC5 Mode, WaveForm, Prescaler and Enable it 
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;      // Set Timer counter mode to 16 bits
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;      // Set TC5 mode as match frequency
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024; // Set prescaler to 1024
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;            // Enable TC5
  TC5->COUNT16.CC[0].reg = (uint16_t) OFF_Time;          // Set TC5 value with ON Time (Stimulation)
  while (tcIsSyncing());
  
  // Configure interrupt request
  NVIC_DisableIRQ(TC5_IRQn);
  NVIC_ClearPendingIRQ(TC5_IRQn);
  NVIC_SetPriority(TC5_IRQn, 0);
  NVIC_EnableIRQ(TC5_IRQn);
  
  TC5->COUNT16.INTENSET.bit.MC0 = 1;           // Enable TC5 Overflow Interrupt Request (OVF)
  while (tcIsSyncing());                       // Wait until TC5 is done syncing 
} 


// .....................................................................................................................


// Check if TC5 syncing is done (true)
bool tcIsSyncing()
{
  return TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY;
}


// .....................................................................................................................


// Enables TC5 and waits for it to be ready
void Timer_Start()
{
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE; //set the CTRLA register
  while (tcIsSyncing()); //wait until snyc'd
}


// .....................................................................................................................


void Timer_Reset()
{
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (tcIsSyncing());
  while (TC5->COUNT16.CTRLA.bit.SWRST);
}


// .....................................................................................................................


void Timer_Disable()
{
  TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (tcIsSyncing());
}


// .....................................................................................................................


void DAC_Init(void)
{  
  PORT->Group[PORTA].DIRSET.reg = PORT_PA02;                  // Configure PA02 (D1 in Trinket M0) to be output
  PORT->Group[PORTA].PINCFG[2].reg |= PORT_PINCFG_PMUXEN;     // Enable the port multiplexer for PA02

  // Odd pin num (2*n+1): use PMUXO
  // Even pin num (2*n): use PMUXE
  PORT->Group[PORTA].PMUX[1].reg = PORT_PMUX_PMUXE_B;         // Connet DAC to PA02. Function B is DAC OUTPUT for PA02      
  
  PM->APBCMASK.reg |= PM_APBCMASK_DAC;                        // Enable Peripheral Clock for DAC
  
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID (DAC_GCLK_ID) |         // DAC share same GCLK
                      GCLK_CLKCTRL_CLKEN |                    // Enable Generic Clock
                      GCLK_CLKCTRL_GEN(0);                    // Select Generic Clock #0
  
  DAC->CTRLA.reg = DAC_CTRLA_SWRST;                           // Apply Software Reset
  while (DAC->CTRLA.reg & DAC_CTRLA_SWRST);                   // Wait Until Reset is Complete
 
  DAC->CTRLA.reg &= ~(DAC_CTRLA_ENABLE);                      // Disable DAC to permit change CTRLA B register.
  DAC->CTRLB.reg |= DAC_CTRLB_EOEN | DAC_CTRLB_REFSEL_AVCC;   // Enable the DAC output on Vout pin. Enable VDDANAL REF. 
  DAC->CTRLA.reg |= DAC_CTRLA_ENABLE;                         // Enable DAC
  while (DAC->STATUS.reg & DAC_STATUS_SYNCBUSY);              // Wait Until Clock is Ok
}


// .....................................................................................................................
