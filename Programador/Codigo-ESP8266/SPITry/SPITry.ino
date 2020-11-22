#include <SPI.h>
#include "libSPSGRF.h"

volatile bool serReceived;
 
uint8_t msj[4] = {0xFF, 0x00, 0x00, 0x00};
uint8_t correctMsgV[4] = {0xFF, 0x85, 0x00, 0x00};
uint8_t incorrectMsgV[4] = {0xFF, 0xE4, 0x00, 0x00};

uint8_t *memAdd;
uint8_t *pAdd;
uint8_t *addMsj;

uint8_t StatusMCU;
uint8_t statusCom;
bool RXReady;
bool TXSent; 

const byte rCom = 0x01;
const byte wCom = 0x00;
const byte cCom = 0x80;

uint8_t memoryA[16];
uint8_t memoryB[16];
uint8_t memoryC[16];
uint8_t tempData[16];

const byte comTX = 0x60;
const byte comRX = 0x61;
const byte comREADY = 0x62;
const byte comSTANDBY = 0x63;
const byte comSLEEP = 0x64; 
const byte comLOCKRX = 0x65;
const byte comLOCKTX = 0x66;
const byte comSABORT = 0x67; 
const byte comRESET = 0x70; 
const byte comFLUSHRX = 0x71;
const byte comFLUSHTX = 0x72; 
const byte addFIFO = 0xFF;
const byte interruptAdd = 0xFA; 
const byte MCStateAdd = 0xC1;

// Primera dirección y luego solo valores a cargar a Add + 1
uint8_t configA1[2] = {0x03, 0x02}; //GPIO_2 configurado como interrupt request, active low
uint8_t configA2[8] = {0x07, 0x36, 0x0D, 0x05, 0x1E, 0xB9, 0x01, 0xAC}; //IF_OFFSET_ANA, IF_OFFSET_DIG, AFC2?, ANA_FUNC_CONF
uint8_t configA3[2] = {0x10, 0x52}; //
uint8_t configA4[3] = {0x9E, 0xD8, 0xA0};
uint8_t configA5[8] = {0x21, 0xE3, 0x36, 0x58, 0x22, 0x62, 0x8A, 0x15};
uint8_t configA6[7] = {0x30, 0x08, 0x04, 0x1E, 0x20, 0x00, 0x04};
uint8_t configA7[6] = {0x36, 0x88, 0x88, 0x88, 0x88, 0x02};
uint8_t configA8[6] = {0x4B, 0xA5, 0x00, 0x00, 0xA5, 0x4F};
uint8_t configA9[6] = {0x50, 0x42, 0x01, 0x08, 0x00, 0x00};
uint8_t configA10[3] = {0x66, 0x04, 0x25}; 
uint8_t configA11[5] = {0x6C, 0x00, 0x70, 0x00, 0x00};
uint8_t configA12[5] = {0x90, 0x00, 0x00, 0x00, 0x05};
uint8_t configA13[2] = {0xA3, 0x35};
uint8_t configA14[6] = {0x1A, 0x93, 0x1A, 0x45, 0x13, 0xC8};
uint8_t configA15[2] = {0x03, 0x02};

uint8_t memoryD[8];

uint8_t tempData1[16];

//const int CS = 10; 
const int CS = D8;
const int SDN = D2;
//const int SDN = 9;

uint8_t counterp; 

uint8_t configCont = 0;

void setup() {
  Serial.begin(115200); // Inicializa comunicación serial BR = 115200
  
  SPI.begin(); // Inicializa comunicación SPI
  
  pinMode(CS, OUTPUT); // Pin de selección de chip configurado como salida
  pinMode(SDN, OUTPUT); // Pin de Shutdown configurado como salida 

  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 
  
  digitalWrite(SDN, LOW); // Pin de Shutdown en bajo para poder utilizar el SPSGRF
  commandSPS(memoryA, comRESET); 
    
  delay(100); // Delay necesario después del RESET

  /*uint8_t state = getStatusMCU();
  Serial.print("Estado: ");
  Serial.println(state);*/

  //loadInitValues();  
  //calibrateTX();
  
  //configCheck();
  
  
  //calibrateRX(); 
     
}

void loop() { 
  tempData1[0] = 0x03;
  tempData1[1] = 0xA2;
  writeSPS(memoryD, 1, tempData1);
  
  readSPS(memoryD, 0x03, 1);
  
  Serial.print("Status Byte HIGH: "); //82
  Serial.println(memoryD[0]);
  Serial.print("Status Byte LOW: "); //7
  Serial.println(memoryD[1]);
  Serial.print("Lectura de Address: "); //162
  Serial.println(memoryD[2]);
  Serial.println("");
  delay(1000);
  
  //delay(1000);
  /*if(serReceived)
  {
    statusCom = 0;
    //TMR1_Intialize(); 
    // Conseguir parametros por UART
    getStatusMCU();
    //contTimer = 0;

    delay(1000); 

    while(contTimer<20) //Contador de tiempo de envío de mensaje (2seg * 20 veces) 
    {
      if(if_time == 1) // Si se enciende la bandera del timer (cada 2 segundos) 
      {
        if_time = 0 // Reinicar bandera
        sendMSG(); 
        contTimer++; // Aumenta el contador
        getInterrupt(); // Interrupción
        LATA = 0; // Reinicar LEDS
        LATD = 0; 
        go_RX_RF
      }

      if(if_rfmodule == 1)
      {
        if_rfmodule = 0;
        getInterupt(); 
        if(RXReady)
        {
          RXReady = false;
          readSPS(memoryA, addFIFO, 3); 
          rogVerif[0] = memoryA[2];
          rogVerif[1] = memoryA[3];
          rogVerif[3] = memoryA[4]; 
          if((memoryA[2] == msj[1]) && (memoryA[3] == msj[2]) && (memoryA[4] == msj[3]))
          {
            LATAbits.LATA5 = 1;
            LATAbits.LATA6 = 1; 
            LATAbits.LATA7 = 1; 
            delay(1000);
            contTimer = 30;
            TMR1_StopTimer();
            sendMSGVerif(true);
            statusCom = 2;
          }
          else
          {
            sendMSGVerif(false);
            statusCom = 1;
            contTimer = 30l
          }
        }
      }
    }
    serialSend(statusCom);
    serReceived = false; 
    
  }*/
  



  
}

void go_RX_RF(void)
{
  delay(50);
  getStatusMCU(memoryA);
  if(StatusMCU == 4) 
  {
    commandSPS(memoryA, comSABORT); 
    commandSPS(memoryA, comFLUSHRX); 
    commandSPS(memoryA, comRX);
  }
  else if(StatusMCU == 1)
  {
    commandSPS(memoryA, comREADY); 
    commandSPS(memoryA, comFLUSHRX);
    commandSPS(memoryA, comRX); 
  }
}

void go_STANDBY_RF(void)
{
  getStatusMCU(memoryA);
  if(StatusMCU == 5)
  {
    commandSPS(memoryA, comSABORT);
    delay(10);
  }
  else if(StatusMCU == 7){
    loadInitValues(); 
    commandSPS(memoryA, comREADY);
  }
  else
  {
    commandSPS(memoryA, comREADY);
  }
}

void sendVerification(bool verif)
{
  readSPS(memoryA, interruptAdd, 4);
  if(verif)
  {
    sendMSGVerif(verif); // Mandar al receptor la verificación 0x85 si esta bien
    statusCom = 1; 
  }
  else
  {
    sendMSGVerif(verif); // Mandar al receptor 0xE4 si esta mal
    statusCom = 2; 
  }
}


void calibrateTX(void)
{
  uint8_t static tempVCO;
  uint8_t state; 
  
  /*tempData[0] = 0xA1; // VCO_CONFIG
  tempData[1] = 0x25;
  writeSPS(memoryB, 1, tempData); // Buena lectura
  
  tempData[0] = 0x50; // PROTOCOL[2]
  tempData[1] = 0xE6;
  writeSPS(memoryB, 1, tempData); // Buena lectura*/

  state = getStatusMCU(memoryB);

  commandSPS(memoryB, 0x65); 
  delay(10);
  readSPS(memoryB, 0xC1, 1);
  Serial.print("Lectura State: ");
  Serial.println(memoryB[2]>>1, HEX);
  state = getStatusMCU(memoryB);

  

  
  //delay(10);
  //Obtener el STATUS para ver si sí llegó a LOCKTX
  /*readSPS(memoryB, 0xC1, 1);
  Serial.print("STATE: ");
  Serial.println(memoryB[2], HEX);
  */
  readSPS(memoryB, 0xE5, 1); // RCO_VCO_CALIBR_OUT[1]
  tempVCO = memoryB[2]&127; 
  tempData[0] = 0x6E; // RCO_VCO_CALIBR_IN[1]
  tempData[1] = tempVCO;
  
  writeSPS(memoryB, 1, tempData); 
  /*readSPS(memoryB, 0x6E, 1);
  Serial.print("0x6E: ");
  Serial.println(memoryB[2], HEX);*/
  
  commandSPS(memoryB, comREADY);
  delay(10);
  tempData[0] = 0x50;
  tempData[1] = 0xE4;
  writeSPS(memoryB, 1, tempData); 

}

void calibrateRX(void)
{
  uint8_t static tempVCO;
  tempData[0] = 0xA1;
  tempData[1] = 0x25;
  writeSPS(memoryA, 1, tempData);
  tempData[0] = 0x50;
  tempData[1] = 0xE6;
  writeSPS(memoryA, 1, tempData);
  commandSPS(memoryA, comLOCKRX);
  delay(100); 
  readSPS(memoryA, 0xE5, 1);
  tempVCO = memoryA[2]&127;
  tempData[0] = 0x6F;
  tempData[1] = tempVCO;
  writeSPS(memoryA, 1, tempData);
  commandSPS(memoryA, comREADY);
  delay(100);
  tempData[0] = 0x50;
  tempData[1] = 0xE4;
  writeSPS(memoryA, 1, tempData);
}

uint8_t getStatusMCU(uint8_t memSpace[16])
{
  uint8_t StateTemp;
  readSPS(memSpace, MCStateAdd, 1); 
  StateTemp = memSpace[2]>>1;

  if(StateTemp == 0x40)
  {
    StatusMCU = 0; // STANDBY
    Serial.println("Estado: STANDBY");
  }
  else if(StateTemp == 0x36)
  {
    StatusMCU = 5; // SLEEP
    Serial.println("Estado: SLEEP");
  }
  else if(StateTemp == 0x03)
  {
    StatusMCU = 1; // READY
    Serial.println("Estado: READY");
  }
  else if(StateTemp == 0x0F)
  {
    StatusMCU = 2; // LOCK
    Serial.println("Estado: LOCK");
  }
  else if(StateTemp == 0x33)
  {
    StatusMCU = 3; // RX
    Serial.println("Estado: RX");
  }
  else if(StateTemp == 0x5F)
  {
    StatusMCU = 4; // TX
    Serial.println("Estado: TX");
  }
  else
  {
    StatusMCU = 7; // ERROR
    Serial.println("Estado: ERROR");
  }
  return StatusMCU;
}

void getInterrupt(void)
{
  uint8_t temp1, temp2; 
  //LATDbits.LATD6 = 0; 
  readSPS(memoryA, interruptAdd, 4);
  temp1 = memoryA[5]&0x01;
  temp2 = memoryA[5]&0x04;
  RXReady = false;
  TXSent = false;

  if(temp1 == 0x01)
  {
    RXReady = true; 
  }
  if(temp1 = 0x04)
  {
    //LATDbits.LATD6 = 1;
    TXSent = true;
  }
}

void sendMSG(void)
{
  //LATDbits.LATD6 = 0;
  delay(10);
  getStatusMCU(memoryA);
  if(StatusMCU == 3)
  {
    commandSPS(memoryA, comSABORT);
    getStatusMCU(memoryA);
    commandSPS(memoryA, comFLUSHTX);
    writeSPS(memoryA, 3, msj);
    commandSPS(memoryA, comTX);
    getStatusMCU(memoryA);
  }
  else if(StatusMCU == 1)
  {
    commandSPS(memoryA, comFLUSHTX);
    writeSPS(memoryA, 3, msj);
    commandSPS(memoryA, comTX);
    getStatusMCU(memoryA);
  }
  //LATDbits.LATD0 = !LATDbits.LATD0;
}

void sendMSGVerif(bool verif) 
{
  //LATDbits.LATD6 = 0;
  delay(10);
  getStatusMCU(memoryA);
  if(StatusMCU == 3)
  {
    commandSPS(memoryA, comSABORT);
    getStatusMCU(memoryA);
    commandSPS(memoryA, comFLUSHTX);
    if(verif)
    {
      writeSPS(memoryA, 3, correctMsgV);
    }
    else
    {
      writeSPS(memoryA, 3, incorrectMsgV);
    }
    commandSPS(memoryA, comTX);
    getStatusMCU(memoryA);
  }
  else if(StatusMCU == 1)
  {
    commandSPS(memoryA, comFLUSHTX);
    if(verif)
    {
      writeSPS(memoryA, 3, correctMsgV); 
    }
    else
    {
      writeSPS(memoryA, 3, incorrectMsgV);
    }
    commandSPS(memoryA, comTX);
    getStatusMCU(memoryA);
  }
  //LATDbits.LATD0 = !LATDbits.LATD0
}

/*void readMSG(void)
{
  // Modo RX 
  sendCommand(0, memAdd);

  memoryA[1] = addFIFO;
  memoryA[2] = addFIFO;
  memoryA[3] = addFIFO; 
  memoryA[4] = addFIFO; 

  moveValues(memAdd, 1, 5);
  sendCommand(8, memAdd);
  
}*/


void loadInitValues(void)
{
  writeSPS(memoryA, 1, configA1);
  writeSPS(memoryA, 7, configA2);
  writeSPS(memoryA, 1, configA3);
  writeSPS(memoryA, 2, configA4);
  writeSPS(memoryA, 7, configA5);
  writeSPS(memoryA, 6, configA6);
  writeSPS(memoryA, 5, configA7);
  writeSPS(memoryA, 5, configA8);
  writeSPS(memoryA, 5, configA9);
  writeSPS(memoryA, 2, configA10);
  writeSPS(memoryA, 4, configA11);
  writeSPS(memoryA, 4, configA12);
  writeSPS(memoryA, 1, configA13);
  writeSPS(memoryA, 5, configA14);
}

void Init(void)
{
  memAdd = memoryA;
  pAdd = memoryA;
  addMsj = msj;
  loadInitValues();
}

void configCheck(void)
{
  readSPS(memoryA, configA2[0], sizeof(configA2)-1);
  if(memoryA[2] == configA2[1])
  {
    if(memoryA[3] == configA2[2])
    {
      if(memoryA[4] == configA2[3])
      {
        if(memoryA[5] == configA2[4])
        {
          if(memoryA[6] == configA2[5])
          {
            if(memoryA[7] == configA2[6])
            {
              if(memoryA[8] == configA2[7])
              {
                configCont += 1; 
              }
            }
          }
        }
      }
    }
  }
  readSPS(memoryA, configA3[0], sizeof(configA3)-1);
  if(memoryA[2] == configA3[1])
  {
    configCont += 1; 
  }
  readSPS(memoryA, configA4[0], sizeof(configA4)-1);
  if(memoryA[2] == configA4[1]){
    if(memoryA[3] == configA4[2]){
      configCont += 1;
    }
  }
  readSPS(memoryA, configA5[0], sizeof(configA5)-1);
  if(memoryA[2] == configA5[1])
  {
    if(memoryA[3] == configA5[2])
    {
      if(memoryA[4] == configA5[3])
      {
        if(memoryA[5] == configA5[4])
        {
          if(memoryA[6] == configA5[5])
          {
            if(memoryA[7] == configA5[6])
            {
              if(memoryA[8] == configA5[7])
              {
                configCont += 1; 
              }
            }
          }
        }
      }
    }
  }
  readSPS(memoryA, configA6[0], sizeof(configA6)-1);
  if(memoryA[2] == configA6[1])
  {
    if(memoryA[3] == configA6[2])
    {
      if(memoryA[4] == configA6[3])
      {
        if(memoryA[5] == configA6[4])
        {
          if(memoryA[6] == configA6[5])
          {
            if(memoryA[7] == configA6[6])
            {
              configCont += 1;
            }
          }
        }
      }
    }
  }
  readSPS(memoryA, configA7[0], sizeof(configA7)-1);
  if(memoryA[2] == configA7[1])
  {
    if(memoryA[3] == configA7[2])
    {
      if(memoryA[4] == configA7[3])
      {
        if(memoryA[5] == configA7[4])
        {
          if(memoryA[6] == configA7[5])
          {
            configCont += 1;
          }
        }
      }
    }
  }
  readSPS(memoryA, configA8[0], sizeof(configA8)-1);
  if(memoryA[2] == configA8[1])
  {
    if(memoryA[3] == configA8[2])
    {
      if(memoryA[4] == configA8[3])
      {
        if(memoryA[5] == configA8[4])
        {
          if(memoryA[6] == configA8[5])
          {
            configCont += 1;
          }
        }
      }
    }
  }
  readSPS(memoryA, configA9[0], sizeof(configA9)-1);
  if(memoryA[2] == configA9[1])
  {
    if(memoryA[3] == configA9[2])
    {
      if(memoryA[4] == configA9[3])
      {
        if(memoryA[5] == configA9[4])
        {
          if(memoryA[6] == configA9[5])
          {
            configCont += 1;
          }
        }
      }
    }
  }
  readSPS(memoryA, configA10[0], sizeof(configA10)-1);
  if(memoryA[2] == configA10[1])
  {
    if(memoryA[3] == configA10[2])
    {
      configCont += 1;
    }
  }
  readSPS(memoryA, configA11[0], sizeof(configA11)-1);
  if(memoryA[2] == configA11[1])
  {
    if(memoryA[3] == configA11[2])
    {
      if(memoryA[4] == configA11[3])
      {
        if(memoryA[5] == configA11[4])
        {
          configCont += 1;
        }
      }
    }
  }
  readSPS(memoryA, configA12[0], sizeof(configA12)-1);
  if(memoryA[2] == configA12[1])
  {
    if(memoryA[3] == configA12[2])
    {
      if(memoryA[4] == configA12[3])
      {
        if(memoryA[5] == configA12[4])
        {
          configCont += 1;
        }
      }
    }
  }
  readSPS(memoryA, configA13[0], sizeof(configA13)-1);
  if(memoryA[2] == configA13[1])
  {
    configCont += 1; 
  }
  readSPS(memoryA, configA14[0], sizeof(configA14)-1);
  if(memoryA[2] == configA14[1])
  {
    if(memoryA[3] == configA14[2])
    {
      if(memoryA[4] == configA14[3])
      {
        if(memoryA[5] == configA14[4])
        {
          if(memoryA[6] == configA14[5])
          {
            configCont += 1;
          }
        }
      }
    }
  }
  readSPS(memoryA, configA1[0], sizeof(configA1)-1);
  if(memoryA[2] = configA1[1])
  {
    configCont += 1;
  }

  if(configCont == 14){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }
  else
  {
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
  }
}






