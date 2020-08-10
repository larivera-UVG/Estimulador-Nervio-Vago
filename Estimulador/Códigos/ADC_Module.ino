// Programa principal para el Trinket M0 del estetoscopio de BITMEC
// PRUEBAS DE CONFIGURACIÓN DEL MODULO ADC A NIVEL DE REGISTROS CON C
// PARA EVITAR USAR LA FUNCION "ANALOGREAD()" DE ARDUINO. ESTA FUNCIÓN
// TIENE UN BUG QUE PROPORCIONA UN OFFSET DE ENTRE 25mV-75mV PERO EN ESTA
// OCASION SE BUSCA EVITAR SU USO YA QUE EL PIN A4 (PA06 EN SAMD21E18A)
// SERA USADO COMO SS DE SPI PARA COMUNICARSE CON UNA MICRO SD.

// ---------------------------------------------------------------------------------------------------

uint32_t ON_Time = 799;

bool flag = 0;
int DAC_signal;
float volt, volt1;
const unsigned char dFactor = 1;


void setup() 
{    

//...................................... Configurar Pines Input/Output  ................................................



//...................................... Configurar Timer (ON/OFF Time) ................................................
      
  Timer_Config();           
  Timer_Start(); 
  My_ADC_Init();   
  My_DAC_Init();

// .....................................................................................................................

}


void loop(){
  
  if (flag==1){
    volt1 = My_ADC_Read();
// --------------------------------------------
    DAC_signal = map(volt1, 0, 4095, 0, 1023);      // Cast 12 bits ADC variable to 10 bits DAC variable
    DAC->DATA.reg = (DAC_signal);                   // Write DAC value
    while(DAC->STATUS.reg & DAC_STATUS_SYNCBUSY);   // Make sure clock synchronization 
// --------------------------------------------
    flag=0;
  }    

}

// .....................................................................................................................


void TC5_Handler (void) 
{
  //volt1 = analogRead(A4);
  //volt1 = My_ADC_Read();
  flag=1;
  TC5->COUNT16.INTFLAG.bit.MC0 = 1;  
}


// .....................................................................................................................


void Timer_Config()
{
  // Enable and configure the Generic CLK Generator (GCLK)
  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |                 // Improve duty cycle 
                     GCLK_GENCTRL_GENEN |               // Enable GCLK
                     GCLK_GENCTRL_SRC_OSC8M |           // OSC32K |          // Set the 32KHz as Clock Source
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
 
  tcReset(); //reset TC5

  // Set TC5 Mode, WaveForm, Prescaler and Enable it 
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;      // Set Timer counter mode to 16 bits
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;      // Set TC5 mode as match frequency
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1;    //024; // Set prescaler to 1024
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;            // Enable TC5
  TC5->COUNT16.CC[0].reg = (uint16_t) ON_Time;          // Set TC5 value with ON Time (Stimulation)
  while (tcIsSyncing());
  
  // Configure interrupt request
  NVIC_DisableIRQ(TC5_IRQn);
  NVIC_ClearPendingIRQ(TC5_IRQn);
  NVIC_SetPriority(TC5_IRQn, 0);
  NVIC_EnableIRQ(TC5_IRQn);
  
  TC5->COUNT16.INTENSET.bit.MC0 = 1;                    // Enable the TC5 interrupt request
  while (tcIsSyncing());                                // Wait until TC5 is done syncing 
} 


// .....................................................................................................................


bool tcIsSyncing()
{
  return TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY;
}


// .....................................................................................................................


void Timer_Start()
{
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;    // Set the CTRLA register
  while (tcIsSyncing());                        // Wait until snyc'd
}


// .....................................................................................................................


void tcReset()
{
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (tcIsSyncing());
  while (TC5->COUNT16.CTRLA.bit.SWRST);
}


// .....................................................................................................................


void tcDisable()
{
  TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (tcIsSyncing());
}


// .....................................................................................................................


void My_DAC_Init(void)
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


void My_ADC_Init(void)
{

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |                 // Improve duty cycle 
                     GCLK_GENCTRL_GENEN |               // Enable GCLK
                     GCLK_GENCTRL_SRC_OSC8M |           // OSC32K |          // Set the 32KHz as Clock Source
                     GCLK_GENCTRL_ID(1);                // Select GCLK5 as ID 
  while (GCLK->STATUS.bit.SYNCBUSY);                    // Wait for synchronization

  REG_PM_APBCMASK |= PM_APBCMASK_ADC;                         // Enable Peripheral Clock for the ADC

  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(ADC_GCLK_ID) |          // ADC share same GCLK
                      GCLK_CLKCTRL_CLKEN |                    // Enable Generic Clock
                      GCLK_CLKCTRL_GEN(1);                    // Select Generic Clock #1
  while (GCLK->STATUS.bit.SYNCBUSY);                          // Wait for bus synchronization

  // .....................................................................................................................

  uint32_t bias = (*((uint32_t *) ADC_FUSES_BIASCAL_ADDR) & ADC_FUSES_BIASCAL_Msk) >> ADC_FUSES_BIASCAL_Pos;
  uint32_t linearity = (*((uint32_t *) ADC_FUSES_LINEARITY_0_ADDR) & ADC_FUSES_LINEARITY_0_Msk) >> ADC_FUSES_LINEARITY_0_Pos;
  linearity |= ((*((uint32_t *) ADC_FUSES_LINEARITY_1_ADDR) & ADC_FUSES_LINEARITY_1_Msk) >> ADC_FUSES_LINEARITY_1_Pos) << 5;
  
  /* Wait for bus synchronization. */
  while (ADC->STATUS.bit.SYNCBUSY) {};
  
  /* Write the calibration data. */
  ADC->CALIB.reg = ADC_CALIB_BIAS_CAL(bias) | ADC_CALIB_LINEARITY_CAL(linearity);

  // .....................................................................................................................

  while (ADC->STATUS.bit.SYNCBUSY);                           // Wait for bus synchronization
  
  ADC->REFCTRL.reg = ADC_REFCTRL_REFSEL_INTVCC1;              // Use the internal VCC reference: 1/2*VDDANA = 0.5*3V3 = 1.65V 

  ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1;                 // Number of Acumulated Samples 

  ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV4 |                 // Set clock prescaler to 512, run the ADC at 8Mhz/512 = 31.25KHz.
                   ADC_CTRLB_RESSEL_12BIT;                    // Set the resolution to 12bit.

  ADC->INPUTCTRL.reg = ADC_INPUTCTRL_GAIN_DIV2 |              // Gain Factor Selection, is 1/2 because voltage ref = 1.65V 
                       //ADC_INPUTCTRL_INPUTSCAN(0x0) |         // Number of Input Channels Included in Scan (Inputscan+1)
                       ADC_INPUTCTRL_MUXNEG_GND |             // Negative Mux Input Selection compared with GND
                       ADC_INPUTCTRL_MUXPOS_PIN1;             // Positive Mux Input Selection (ADC AIN1 pin)

  PORT->Group[PORTA].DIRCLR.reg = PORT_PA03;                  // Configure PA03 to be Input
  PORT->Group[PORTA].PINCFG[3].reg |= PORT_PINCFG_PMUXEN;     // Enable the port multiplexer for PA03
  PORT->Group[PORTA].PMUX[1].reg = PORT_PMUX_PMUXO_B;         // Connect AIN[1] to PA03. Function B is Analog Input #1     
  
  while (ADC->STATUS.bit.SYNCBUSY);                           // Wait for bus synchronization
  ADC->CTRLA.bit.ENABLE = true;                               // Enable ADC

  uint16_t dummy_read = My_ADC_Read();

//  ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1 |                // Number of Acumulated Samples 
//                     ADC_AVGCTRL_ADJRES(0x0);                 // Set Averaging to 1 Sample

  //ADC->CTRLA.reg = ADC_CTRLA_SWRST;                           // Apply Software Reset
  //while (ADC->CTRLA.reg & ADC_CTRLA_SWRST);                   // Wait Until Reset is Complete
    
  //ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_DIV2_Val;      // Default Analog Reference
  //ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val;   // 1/2 VDDANA = 0.5*3V3 = 1.65V  
  //REG_ADC_CTRLA |= ADC_CTRLA_ENABLE;                          // Enable ADC Module  
  //while (ADC->STATUS.bit.SYNCBUSY);                           // Wait for Enable
                     
  //REG_ADC_EVCTRL |= ADC_EVCTRL_RESRDYEO;                      // Result Ready Event Out is enabled and an event will be generated.
  //REG_ADC_SAMPCTRL |= ADC_SAMPCTRL_RESETVALUE;                // ADC Reset
  
}


// .....................................................................................................................

  
uint16_t My_ADC_Read()
{

  while (ADC->STATUS.bit.SYNCBUSY);                           // Wait for bus synchronization.
  ADC->SWTRIG.bit.START = true;                               // Start the ADC using a software trigger
  while (ADC->INTFLAG.bit.RESRDY == 0);                       // Waiting for conversion to complete
  ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;

  uint16_t resultado = ADC->RESULT.reg;
  
  return resultado;
  
  //ADC->CTRLA.bit.ENABLE |= ADC_CTRLA_ENABLE;                  // Enable ADC
  //ADC->SWTRIG.bit.START |= ADC_SWTRIG_START;                  // ADC Start Conversion
  //while ((ADC->INTFLAG.bit.RESRDY == 0));                     // Waiting for conversion to complete
  //uint16_t Result = ADC->RESULT.reg;// = REG_ADC_RESULT;
  //return Result;
}


// .....................................................................................................................
