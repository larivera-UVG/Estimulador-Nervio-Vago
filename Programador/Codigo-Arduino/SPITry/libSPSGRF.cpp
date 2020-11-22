/**
 * Creado por Miguel Alvarez - 16168
 * Universidad del Valle de Guatemala - Facultad de Ingenería
 * Departamento de Ingeniería Mecatrónica
 * Módulo de Programación - Proyecto de Neuroestimulación del Nervio Vago 
 * Fase 2
 * 
 * Basado en la librería SPI de Microchip para sus PIC10, PIC12, PIC16 y PIC18 
 * y basado en el código realizado por Andrés Girón para la Fase 1 del Proyecto
 * 
 * Librería para el uso del SPSGRF(C) con Arduino Uno/NodeMCU ESP-12E
 * 
 * Archivo cpp 
 **/
 
#include "libSPSGRF.h" 

#define DUMMY_DATA 0x0 

SPISettings settingsA(8000000, MSBFIRST, SPI_MODE0); // Configuración para SPI definida con CLK = 8MHz, MSB de primero y modo 0
//2000000 antes



const int CS = D8; // Chip/Slave Select en el pin 10 


uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
  
  SPI.beginTransaction(settingsA); // Se inicia la transacción SPI con la configuración definida
  digitalWrite(CS, LOW); // Activa la línea CS para iniciar la operación
  
  uint8_t bytesWritten = 0; // Se define una variable contador para la cantidad de bytes escritos 

  if(bufLen != 0) // Si el número de bytes a ser intercambiado no es 0
  {
    if(dataIn != NULL) // Si se desea escribir 
    {
      while(bytesWritten < bufLen) // Mientras el contador de bytes no haya superado el número de bytes deseado
      {
        if(dataOut == NULL) // Si no se desea leer 
        {
          SPI.transfer(dataIn[bytesWritten]); // Se transmite los datos de dataIn según la posición que indica el contador
        }
        else // Si se desea leer 
        {
          dataOut[bytesWritten] = SPI.transfer(dataIn[bytesWritten]); // Se almacena en dataOut la lectura indicada por el contador
                                                                      // y se transmite dataIn en la posición indicada por el contador
        }

        bytesWritten++; // Se aumenta el contador de bytes
      }
    }
    else // Si no se desea escribir 
    {
      if(dataOut != NULL) // Si no se desea escribir 
      {
        while(bytesWritten < bufLen) // Mientras el contador de bytes no haya superado el número de bytes deseado
        {
          dataOut[bytesWritten] = SPI.transfer(DUMMY_DATA); // Se almacena la lectura en dataOut y no se transmite nada importante
          bytesWritten++; // Se aumenta el contador de bytes
        }
      }
    }
  }

  digitalWrite(CS, HIGH); // Se desactiva la línea CS para finalizar la operación 
  SPI.endTransaction(); // Se finaliza la transacción SPI
  
  return bytesWritten; // Se retorna el número de bytes intercambiados 
}

void writeSPS(uint8_t *mem, uint8_t bytes, uint8_t *currentAdd)
{
  for(int i = 0; i <= bytes; i++) // Ciclo for desde 0 hasta la cantidad de bytes que se desea escribir
  {
    mem[i+1] = currentAdd[i]; // Se almacenan las direcciones a las que se desea escribir desde la posición 1 de mem
  }
  mem[0] = 0x00; // Se almacena el comando de escritura en la posición 0 de mem
  SPI_Exchange8bitBuffer(mem, bytes + 2, mem); // Se intercambian los datos por medio de SPI
  /** 
   * Explicación:
   * 
   * En la primera posición se encuentra mem, que se usa para transmitir el comando de escritura y las direcciones a las que se desea escribir
   * En la segunda posición va el número de bytes + 2. El SPSGRF(C) siempre requiere de 2 bytes antes de recibir los datos que se quieren escribir,
   * el primer byte es el comando de escritura y el segundo es para la dirección a la que se desea escribir, luego ya van los datos
   * En la tercera posición otra vez está mem, que guarda la lectura por SPI. No es necesario mantener el comando de escritura y la dirección. 
   */
}

void readSPS(uint8_t *mem, uint8_t addressToRead, uint8_t bytes)
{
  uint8_t bytesToRead = 0; // Variable para almacenar la cantidad total de bytes a leer
  bytesToRead = bytes + 2; // Se suman 2 bytes para tomar en cuenta los bits de estado que se devuelven mientras 
                           // se envían el comando de lectura y la dirección que se desea leer
  mem[0] = 0x01; // Se almacena el comando de lectura en la posición 0 de mem
  mem[1] = addressToRead; // Se almacena la dirección que se desea leer en la posición 1 de mem
  SPI_Exchange8bitBuffer(mem, bytesToRead, mem); // Se intercambian los datos por medio de SPI
}

void commandSPS(uint8_t *mem, uint8_t command)
{
  mem[0] = 0x80; // Se guarda el comando para enviar comandos en la posición 0 de mem
  mem[1] = command; // Se guarda el comando deseado en la posición 1 de mem
  SPI_Exchange8bitBuffer(mem, 2, mem); // Se intercambian los datos por medio de SPI
}





