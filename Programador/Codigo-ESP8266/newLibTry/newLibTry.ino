#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(2, 4); // CE, CSN
const byte addresses [][6] = {"00001", "00002"};  //Setting the two addresses. One for transmitting and one for receiving

void setup() {

  Serial.begin(115200);
  radio.begin();                           //Starting the radio communication
  radio.openWritingPipe(addresses[1]);     //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[0]);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN); //You can set it as minimum or maximum depending on the distance between the transmitter and receiver. 
}
void loop() 
{  
  delay(5);
  radio.stopListening();                             //This sets the module as transmitter

  uint8_t data[2]; 
  data[0] = 55;
  data[1] = 66; 
      
  radio.write(&data, sizeof(data));  //Sending the data
  delay(5);

  uint8_t dataIn[2];
      
  radio.startListening();                            //This sets the module as receiver

  /*if(radio.available())
  {
    radio.read(&dataIn, sizeof(dataIn));
    Serial.println(dataIn[0]);
    Serial.println(dataIn[1]);
  }*/
  while(!radio.available());                         //Looking for incoming data
  radio.read(&dataIn, sizeof(dataIn)); //Reading the data
  Serial.println(dataIn[0]);
  Serial.println(dataIn[1]);
  

}
