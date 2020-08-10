// Period or Top value for count 
// freq = GCLK4_freq/(TCC0_Prescaler*(1+TOP_Value))
volatile unsigned int period = 31999;

// Variable to generate duyty cycle of PWM
volatile float duty_cycle = 0.00013;

// Select Gen Clock to setting the waveform generator clock or sample rate
const unsigned char gClock = 4;

// Set the divide factor for the Gen Clock, 48MHz/3 = 16MHz
const unsigned char dFactor = 1;

// Array for frequency configuration or top value for a 30, 25, 20, 15, 10, 5, 2 and 1Hz 
// repectively, of the Stimulation Signal. 
const unsigned int PWM_Freq[3][8] = {{1561, 1874, 2343, 3124, 4687, 9374, 23437, 46874},    // 48MHz
                                     {2082, 2499, 3124, 4166, 6249, 12499, 31249, 62499},   // 8MHz
                                     {1066, 1279, 1599, 2132, 3199, 6399, 15999, 31999}};   // 32KHz

// Array for CCx values for 1ms, 750us, 500us, 250us and 130us respectively, for pulse 
// width or hight state in the square signal (PWM) during the Stimulation Time
const unsigned char pulse_width[3][5] = {{47, 35, 23, 12, 6},   // 48MHz
                                         {62, 47, 31, 16, 8},   // 8MHz
                                         {32, 24, 16, 8, 4}};   // 32KHz

void setup()
{
  pinMode(0, OUTPUT);

  // Enable and configure the Generic CLK Generator (GCLK)
  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |               // Improve duty cycle 
                     GCLK_GENCTRL_GENEN |             // Enable GCLK
                     GCLK_GENCTRL_SRC_OSC32K |        // Set the 32KHz as Clock Source
                     GCLK_GENCTRL_ID(gClock);         // Select GCLK4 as ID 
  while (GCLK->STATUS.bit.SYNCBUSY);                  // Wait for synchronization


  // Select clock divider to GCLK4
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(dFactor) |        // Divide 32KHz by 1
                    GCLK_GENDIV_ID(gClock);           // Apply it to GCLK4 
  while (GCLK->STATUS.bit.SYNCBUSY);                  // Wait for synchronization


  // Enable GCLK4 and connect it to TCC0 and TCC1
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |             // Enable Generic Clock 
                     GCLK_CLKCTRL_GEN_GCLK4 |         // Select GCLK4
                     GCLK_CLKCTRL_ID_TCC0_TCC1;       // Feed CLK4 to TCC0 and TCC1
  while (GCLK->STATUS.bit.SYNCBUSY);                  // Wait for synchronization


  // Divide counter by 1 (This is N)
  TCC0->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV1;
  //TCC0->CTRLA.reg |= TCC_CTRLA_PRESCALER(TCC_CTRLA_PRESCALER_DIV1_Val);

  // Set Timer counter Mode to 16 bits
  TCC0->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;


  // Use Normal PWM (Single-slope): count up to PER, match on CC[n]
  TCC0->WAVE.reg = TCC_WAVE_WAVEGEN_NPWM;             // Select NPWM as waveform
  while (TCC0->SYNCBUSY.bit.WAVE);                    // Wait for synchronization


  // Set the period (TOP) before resetting timer
  TCC0->PER.reg = period;                              // Set the rate or frequency of PWM signal
  while (TCC0->SYNCBUSY.bit.PER);                     // Wait for synchronization


  // Set duty cycle where n for CC[n] is n = x % 4 and x is form WO[x]
  TCC0->CC[0].reg = period*duty_cycle;                // Set PWM signal to 50% of duty cicle 
  while (TCC0->SYNCBUSY.bit.CC0);                     // Wait for synchronization


  // Configure PA08 (D0 in Trinket) to be output
  PORT->Group[PORTA].DIRSET.reg = PORT_PA08;          // Set pin as output
  PORT->Group[PORTA].OUTCLR.reg = PORT_PA08;          // Set pin to low

  // Enable the port multiplexer for PA08
  PORT->Group[PORTA].PINCFG[8].reg |= PORT_PINCFG_PMUXEN;

  // Connet TCC1 timer to PA08. Function E is TCC0/WO[0] for PA08 (function F is TCC1/WO[2])
  // Odd pin num (2*n+1): use PMUXO
  // Even pin num (2*n): use PMUXE
  PORT->Group[PORTA].PMUX[4].reg = PORT_PMUX_PMUXE_E;

  //PORT->Group[g_APinDescription[3].ulPort].PINCFG[g_APinDescription[3].ulPin].bit.PMUXEN = 1;
  //PORT->Group[g_APinDescription[4].ulPort].PMUX[g_APinDescription[4].ulPin >> 1].reg = PORT_PMUX_PMUXO_F | PORT_PMUX_PMUXE_F;

//  REG_TCC1_INTENSET = TCC_INTENSET_OVF;
//  enable_interrupts();


  // Enable TCC1 to start (Start PWM)
//  REG_TCC1_CTRLA |= TCC_CTRLA_PRESCALER_DIV1 |        // Divide GCLK4 by 1
//                    TCC_CTRLA_ENABLE;                 // Enable the TCC0 output
  TCC0->CTRLA.reg |= (TCC_CTRLA_ENABLE);              // Enable TCC1 output
  while (TCC0->SYNCBUSY.bit.ENABLE);                  // Wait for synchronization

}


void loop() {

}


//void enable_interrupts() {
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
//}
