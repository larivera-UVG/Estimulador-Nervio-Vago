 
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
                                     {1041, 1249, 1562, 2082, 3124, 6249, 15624, 31249},    // 8MHz
                                     {1066, 1279, 1599, 2132, 3199, 6399, 15999, 31999}};   // 32KHz

// CCx values for 1ms, 750us, 500us, 250us and 130us respectively, for pulse 
// width or hight state in the square signal (PWM) during the Stimulation Time
const unsigned char PWM_pw[3][5] = {{47, 35, 23, 12, 6},   // 48MHz
                                    {31, 23, 16, 8, 4},    // 8MHz
                                    {32, 24, 16, 8, 4}};   // 32KHz

// Array for CCx values for 600, 300, 180, 108, 66, 60 48, 30, 21, 18, 14, 7, 2, 1s respectively, for
// On/Off time for Stimulation Signal. Clock at 32KHz
const unsigned int ON_OFF_TIME[14] = {18749, 9374, 5624, 3374, 2062, 1874, 1499, 937, 655, 562, 437, 218, 62, 30};


// ........................................ PWM and Timer Values Selection .............................................


volatile unsigned int period;         // = PWM_freq[0][3];
volatile float pulse_width;           // = period*0.25; //PWM_pw[2][0];     
volatile int ON_Time;                 // = ON_OFF_TIME[13];
volatile int OFF_Time;                // = ON_OFF_TIME[13];


// ............................... Variables for PWM, Timer and Digital Potentiometer ..................................


// Select Gen Clock to setting the waveform generator clock or sample rate
const unsigned char gClock = 4;
byte PWM_CLK; 

const byte UD = 1;
const byte INC = 2;
const byte CS = 3;

bool flag = 0;
byte mode = 0;
bool Ramp_mode = false; 
bool go_to_sleep = false;

int pulsos = 0;
int amplitude_max = 98;
int amplitude_min = 1;

int amplitude;
int frecuencia = 5;
int Stimulation_time = 7;
int Repose_time = 48;

float ramp_interval;
int timer_interval;

// .....................................................................................................................


void setup()
{

//PM->CPUSEL.reg = PM_CPUSEL_CPUDIV(4);

//...................................... Set Input/Output Pins Mode Configuration ......................................
  
  pinMode(0, OUTPUT);                 // VNS Stimulation Signal Output
  pinMode(UD, OUTPUT);                // U/'D
  pinMode(INC, OUTPUT);               // 'INC
  pinMode(CS, OUTPUT);                // 'CS

  digitalWrite(UD, HIGH);
  digitalWrite(INC, HIGH);

// .....................................................................................................................

  switch (frecuencia) 
  { 
    case 1:
      period = PWM_freq[1][7];    
      break;
    case 2:
      period = PWM_freq[1][6];
      break;       
    case 5:
      period = PWM_freq[1][5];
      break;       
    case 10:
      period = PWM_freq[1][4];
      break;
    case 15:
      period = PWM_freq[1][3];
      break;
    case 20:
      period = PWM_freq[1][2];
      break;
    case 25:
      period = PWM_freq[1][1];
      break; 
    case 30:
      period = PWM_freq[1][0];
      break;                                           
    default:
      period = PWM_freq[1][7];
      break;
  }

  pulse_width = PWM_pw[1][0];
  //pulse_width = period*0.5;

  switch (Stimulation_time) 
  { 
    case 1:
      ON_Time = ON_OFF_TIME[13];    
      break;
    case 2:
      ON_Time = ON_OFF_TIME[12]; 
      break;       
    case 7:
      ON_Time = ON_OFF_TIME[11]; 
      break;       
    case 14:
      ON_Time = ON_OFF_TIME[10]; 
      break;
    case 18:
      ON_Time = ON_OFF_TIME[9]; 
      break;
    case 21:
      ON_Time = ON_OFF_TIME[8]; 
      break;
    case 30:
      ON_Time = ON_OFF_TIME[7]; 
      break; 
    case 48:
      ON_Time = ON_OFF_TIME[6]; 
      break;    
    case 60:
      ON_Time = ON_OFF_TIME[5]; 
      break;                 
    case 66:
      ON_Time = ON_OFF_TIME[4]; 
      break; 
    case 108:
      ON_Time = ON_OFF_TIME[3]; 
      break;     
    case 180:
      ON_Time = ON_OFF_TIME[2]; 
      break;
    case 300:
      ON_Time = ON_OFF_TIME[1]; 
      break;          
    case 600:
      ON_Time = ON_OFF_TIME[0]; 
      break;     
    default:
      ON_Time = ON_OFF_TIME[7];
      break;
  }


  switch (Repose_time) 
  { 
    case 1:
      OFF_Time = ON_OFF_TIME[13];    
      break;
    case 2:
      OFF_Time = ON_OFF_TIME[12]; 
      break;       
    case 7:
      OFF_Time = ON_OFF_TIME[11]; 
      break;       
    case 14:
      OFF_Time = ON_OFF_TIME[10]; 
      break;
    case 18:
      OFF_Time = ON_OFF_TIME[9]; 
      break;
    case 21:
      OFF_Time = ON_OFF_TIME[8]; 
      break;
    case 30:
      OFF_Time = ON_OFF_TIME[7]; 
      break; 
    case 48:
      OFF_Time = ON_OFF_TIME[6]; 
      break;    
    case 60:
      OFF_Time = ON_OFF_TIME[5]; 
      break;                 
    case 66:
      OFF_Time = ON_OFF_TIME[4]; 
      break; 
    case 108:
      OFF_Time = ON_OFF_TIME[3]; 
      break;     
    case 180:
      OFF_Time = ON_OFF_TIME[2]; 
      break;
    case 300:
      OFF_Time = ON_OFF_TIME[1]; 
      break;          
    case 600:
      OFF_Time = ON_OFF_TIME[0]; 
      break;     
    default:
      OFF_Time = ON_OFF_TIME[0];
      break;
  }

  if (frecuencia >= 10)
  {
    Ramp_mode = true;  
  }
  else
  {
    Ramp_mode = false;  
  }

  
//...................................... Configurare PWM (Stimulation signal) ..........................................

  PWM_Config();
  Enable_PWM_Interrupts();  
  //PWM_Start();

// ..................................... Configurar parametros de la rampa .............................................

if (Ramp_mode == true)
{

  amplitude = amplitude_min;                                  // Ramp-up Starts in Amplitude = 1
  
  ramp_interval = (amplitude_max-1)/2;            // (98-1)/2s = 48.5Hz => 20.62ms
  timer_interval = (7812.5/ramp_interval)-1;      // (46875.0/ramp_interval)-1;     // (46,875.0/48.5)-1 = 965.49 => 965 

  Timer2_Config();                                // Configurate Timer for Ramp Amplitude Refresh
  Timer2_Interrupts();                            // Enable Ramp Amplitude Refresh
  Timer2_Start();                                 // Start Timer for Ramp Amplitude Refresh
}
else
{
  amplitude = amplitude_max;
  //PWM_Start();
}

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
    setResistance(amplitude);     
    flag=0;
  }

  if(go_to_sleep)
  {
    go_to_sleep = false;
    SAMD21_Sleep();    
  }
  
}


// .....................................................................................................................


void TCC0_Handler()
{

  if(mode==2)
  {
    pulsos++;
    if(pulsos==frecuencia) 
    {
      pulsos=0;
      if(Ramp_mode == true) amplitude--;
      flag=1;     
    } 
     
  }

  TCC0->INTFLAG.bit.MC0 = 1;                            // Clear interrupt flag
  
}


// .....................................................................................................................


void TCC1_Handler()
{

  if(mode==1) amplitude++;              // Increment Amplitude for Ramp-up 
  else if(mode==3) amplitude--;         // Decrement Amplitude for Ramp-down

  if(amplitude > amplitude_max) amplitude = amplitude_max;  
  if(amplitude < amplitude_min) amplitude = amplitude_min;
  flag = 1;

  TCC1->INTFLAG.bit.MC0 = 1;            
  
}


// .....................................................................................................................


void setResistance(int percent){ 
  digitalWrite(UD, LOW);                // Select Decrement Counter
  digitalWrite(CS, LOW);                // Select Digital Potenciometer
    
  for (int i=0; i<100; i++){            // Increment/Decrement Counter
    digitalWrite(INC, LOW);             // Low State (this gives a negative edge)
    delayMicroseconds(5);               
    digitalWrite(INC, HIGH);            // High State 
    delayMicroseconds(5);
  }

  digitalWrite(UD, HIGH);               // Select Increment Counter
  for (int i=0; i<percent; i++){        // Increment/Decrement Counter
    digitalWrite(INC, LOW);             // Low State (this gives a negative edge)
    delayMicroseconds(5);
    digitalWrite(INC, HIGH);            // High State 
    delayMicroseconds(5);
  }

  //digitalWrite(CS, HIGH);               // Save counter in non-volatile memory and enter in Stand-By Mode
}


// .....................................................................................................................


void TC5_Handler (void) {

  if(Ramp_mode == true)
  {
    mode++;                                             // Ramp Up -> ON Time -> Ramp Down -> OFF Time
    if(mode>=5) mode=1;                                 // Reset Stimultation Sequence    
  }
  else
  {
    if(mode==2) mode = 4;                               // ON Time -> OFF Time
    else if(mode==4) mode = 2;
    else mode = 2;                                      // Reset Stimultation Sequence 
  } 

  
  if(mode == 1)
  {
    
    Timer_Disable();                                    // Stop Timer to change to Ramp Up Time (2S)
    TC5->COUNT16.CC[0].reg = (uint16_t) 62;             // Set TC5 value with Ramp Up Time (2S)   
    PWM_Start();                                        // Start PWM
    Timer_Start();                                      // Enable Timer again    

    Timer2_Start();                                     // Update Ramp Amplitude
    
  }
  else if(mode == 2)
  {

    Timer2_Stop();
    
    pulsos=0;
    Timer_Disable();                                    // Stop Timer to change to ON time value       
    TC5->COUNT16.CC[0].reg = (uint16_t) ON_Time;        // Set TC5 value with ON Time (Stimulation)    
    if(Ramp_mode == false) PWM_Start();                 // Enable PWM 
    Timer_Start();                                      // Enable Timer again    
     
  } 
  else if(mode == 3) 
  { 
       
    Timer_Disable();                                    // Stop Timer to change to Ramp Down Time
    TC5->COUNT16.CC[0].reg = (uint16_t) 62;             // Set TC5 value with Ramp Down Time    
    Timer_Start();                                      // Enable Timer again     

    Timer2_Start();                                     // Update Ramp Amplitude
                  
  }
  else if(mode == 4)
  {

    Timer2_Stop();
    
    PWM_Stop();                                         // Disable PWM     
    Timer_Disable();                                    // Stop Timer to change to OFF Time Value
    TC5->COUNT16.CC[0].reg = (uint16_t) OFF_Time;       // Set TC5 value with OFF Time (Repose)    
    Timer_Start();                                      // Enable Timer again    
    digitalWrite(0, LOW);     

    go_to_sleep = true;
    
  }
       
  TC5->COUNT16.INTFLAG.bit.MC0 = 1;                     // Clear interrupt flag  
  
}


// .....................................................................................................................


void PWM_Config()
{

  PM->APBCMASK.reg |= PM_APBCMASK_TCC0;
  //GCLK_GENCTRL_RUNSTDBY |             // Set GCLK4 to run in standby mode 


  // Enable and configure the Generic CLK Generator (GCLK)
  GCLK->GENCTRL.reg = GCLK_GENCTRL_IDC |                  // Improve duty cycle 
                      GCLK_GENCTRL_GENEN |                // Enable GCLK
                      GCLK_GENCTRL_SRC_OSC8M |            //DFLL48M |           // OSC32K | OSC8M | DFLL48M |   // Set the 48MHz as Clock Source
                      GCLK_GENCTRL_ID(gClock);            // Select GCLK4 as ID 
  while (GCLK->STATUS.bit.SYNCBUSY);                      // Wait for synchronization


  // Select clock divider to GCLK4
  GCLK->GENDIV.reg = GCLK_GENDIV_DIV(1) |                 // Divide 48MHz by 1 
                     GCLK_GENDIV_ID(gClock);              // Apply it to GCLK4    
  while (GCLK->STATUS.bit.SYNCBUSY);                      // Wait for synchronization

  
  // Enable GCLK4 and connect it to TCC0 and TCC1
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |                // Enable Generic Clock 
                      GCLK_CLKCTRL_GEN_GCLK4 |            // Select GCLK4
                      GCLK_CLKCTRL_ID_TCC0_TCC1;          // Feed CLK4 to TCC0 and TCC1
  while (GCLK->STATUS.bit.SYNCBUSY);                      // Wait for synchronization


  TCC0->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV256;    //DIV1024;         // Divide counter by 1 (This is N)
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
  GCLK->GENCTRL.reg = GCLK_GENCTRL_RUNSTDBY |           // Set GCLK5 to run in standby mode
                      GCLK_GENCTRL_IDC |                // Improve duty cycle 
                      GCLK_GENCTRL_GENEN |              // Enable GCLK
                      GCLK_GENCTRL_SRC_OSC32K |         // Set the 32KHz as Clock Source
                      GCLK_GENCTRL_ID(5);               // Select GCLK5 as ID 
  while (GCLK->STATUS.bit.SYNCBUSY);                    // Wait for synchronization


  // Select clock divider to GCLK5
  GCLK->GENDIV.reg = GCLK_GENDIV_DIV(1) |               // Divide 32KHz by 1
                     GCLK_GENDIV_ID(5);                 // Apply it to GCLK5 
  while (GCLK->STATUS.bit.SYNCBUSY);                    // Wait for synchronization


  // Enable GCLK0 and connect it to TC4 and TC5
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |              // Enable Generic Clock 
                      GCLK_CLKCTRL_GEN_GCLK5 |          // Select GCLK5
                      GCLK_CLKCTRL_ID_TC4_TC5;          // Feed CLK5 to TC4 and TC5
  while (GCLK->STATUS.bit.SYNCBUSY);                    // Wait for synchronization

 
  Timer_Reset(); //reset TC5

  // Set TC5 Mode, WaveForm, Prescaler and Enable it 
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_RUNSTDBY |           // Set the timer to run in standby mode
                           TC_CTRLA_MODE_COUNT16 |       // Set Timer counter mode to 16 bits
                           TC_CTRLA_WAVEGEN_MFRQ |       // Set TC5 mode as match frequency
                           TC_CTRLA_PRESCALER_DIV1024 |  // Set prescaler to 1024
                           TC_CTRLA_ENABLE;              // Enable TC5

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


void Timer_Start()
{
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;    // set the CTRLA register
  while (tcIsSyncing());                        // wait until snyc'd
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


void Timer2_Config()
{

  TCC1->WAVE.reg = TCC_WAVE_WAVEGEN_MFRQ;                 // Select NPWM (Single-slope): count up to PER, match on CC[n]
  TCC1->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV1024;         // Divide counter by 1 (This is N)
  while (TCC1->SYNCBUSY.bit.WAVE);                        // Wait for synchronization

  TCC1->CC[0].reg = timer_interval; //961;                // Set PWM signal to 50% of duty cicle 
  while (TCC1->SYNCBUSY.bit.CC0);                         // Wait for synchronization

}


// .....................................................................................................................


void Timer2_Interrupts()
{
  
  NVIC_DisableIRQ(TCC1_IRQn);
  NVIC_ClearPendingIRQ(TCC1_IRQn);
  NVIC_SetPriority(TCC1_IRQn, 1);
  NVIC_EnableIRQ(TCC1_IRQn);

  TCC1->INTENSET.bit.MC0 = 1;                           // Enable TC5 Overflow Interrupt Request (OVF)
  while(TCC1->STATUS.reg & TC_STATUS_SYNCBUSY); 
  
} 


// .....................................................................................................................

void Timer2_Start()
{ 
  TCC1->CTRLA.reg |= (TCC_CTRLA_ENABLE);              // Enable TCC1 (Start PWM)
  while (TCC1->SYNCBUSY.bit.ENABLE);                  // Wait for synchronization     
}


// .....................................................................................................................


void Timer2_Stop()
{
  TCC1->CTRLA.reg &= (~TCC_CTRLA_ENABLE);             // Disable TCC1 (Stop PWM)
  while (TCC1->SYNCBUSY.bit.ENABLE);                  // Wait for synchronization
}


// .....................................................................................................................


void Timer2_Reset()
{
  TCC1->CTRLA.reg = TCC_CTRLA_SWRST;
  while (TCC1->CTRLA.bit.SWRST);
}


// .....................................................................................................................


void SAMD21_Sleep()
{
  // Due to a hardware bug on the SAMD21, the SysTick interrupts become active before the flash has powered up from sleep, causing a hard fault
  // To prevent this the SysTick interrupts are disabled before entering sleep mode
  
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;             // Disable SysTick interrupts
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;                      // Put the SAMD21 in deep sleep upon executing the __WFI() function
  SYSCTRL->VREG.bit.RUNSTDBY = 1;                         // Keep the voltage regulator in normal configuration during run stanby
  SYSCTRL->OSC32K.bit.RUNSTDBY = 1;                       // Set the Internal 32KHz crystal to run standby mode
  SYSCTRL->OSC8M.bit.RUNSTDBY = 1;                        // Set the Internal 8MHz crystal to run standby mode 
  NVMCTRL->CTRLB.reg |= NVMCTRL_CTRLB_SLEEPPRM_DISABLED;  // Disable Auto Power Reduction During Sleep - SAMD21 Errata 1.14.2
  __WFI();                                                // Put the SAMD21 into Deep Sleep, Zzzzzzzz...   
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;              // Enable SysTick interrupts 
  
}


// .....................................................................................................................
  
