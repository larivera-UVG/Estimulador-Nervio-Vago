#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> 

RF24 radio(9, 10); //CE, CSN

const byte addresses [][6] = {"00001", "00002"};

uint8_t dataBus[2]; 

uint8_t dataOut[2]; 

void setup()
{
  Serial.begin(115200);

  if(!radio.begin())
  {
    Serial.println("No se prendio");
  }
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);

  dataOut[0] = 12; 
  dataOut[1] = 54;
}

void loop()
{
  delay(5); 
  radio.startListening();
  if(radio.available())
  {
    radio.read(&dataBus, sizeof(dataBus));
    Serial.println(dataBus[0]);
    Serial.println(dataBus[1]);
  }
  delay(5); 

  radio.stopListening(); 
  radio.write(dataOut, sizeof(dataOut));
}
