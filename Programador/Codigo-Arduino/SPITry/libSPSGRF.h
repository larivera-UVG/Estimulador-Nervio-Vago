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
 * Archivo header
 **/
 
#ifndef LIBSPSGRF_H
#define LIBSPSGRF_H

#include <Arduino.h>
#include <SPI.h>


/**
 * uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);
 * 
 * Utilizada para intercambiar un buffer de datos por SPI
 * 
 * Parámetros:
 * uint8_t *dataIn -  Buffer de datos a ser transmitido por SPI 
 * uint8_t bufLen - Número de bytes a ser intercambiado
 * uint8_t *dataOut - Buffer de datos a ser recibidos por SPI
 * 
 * Retorna:
 * uint8_t bytesWritten - El número de bytes intercambiado por SPI
 **/
uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);

/**
 * void writeSPS(uint8_t *mem, uint8_t bytes, uint8_t *currentAdd);
 * 
 * Utilizada para escribir datos al módulo SPSGRF(C) (a registros o al queue FIFO)
 * 
 * Parámetros: 
 * uint8_t *mem - Array en el que se almacena el comando de escritura y las direcciones
 *                a las cuales se les desea escribir. 
 *                También se usa para almacenar lo que devuelve el SPSGRF
 *                
 * uint8_t bytes - Número de bytes que se va a escribir 
 * uint8_t *currentAdd - Array de direcciones a las que se desea escribir
 * 
 * Retorna:
 * Nada
 **/
void writeSPS(uint8_t *mem, uint8_t bytes, uint8_t *currentAdd);

/**
 * void readSPS(uint8_t *mem, uint8_t adddressToRead, uint8_t bytes);
 * 
 * Utilizada para leer datos del módulo SPSGRF(C) (de registros o del queue FIFO)
 * 
 * Parámetros: 
 * uint8_t *mem - Array en el que se almacena el comando de lectura y las dirección
 *                que se desea leer. 
 *                También se usa para almacenar lo que devuelve el SPSGRF
 *                
 * uint8_t addressToRead - Dirección que se desea leer 
 * uint8_t bytes - Número de bytes que se desean leer
 * 
 * Retorna:
 * Nada
 */
void readSPS(uint8_t *mem, uint8_t addressToRead, uint8_t bytes);

/**
 * void commandSPS(uint8_t *mem, uint8_t command); 
 * 
 * Utilizada para enviar comandos al módulo SPSGRF(C) 
 * Los comandos se utilizan para cambiar el modo de operación, activar y desactivar funciones, entre otras cosas
 * 
 * Parámetros: 
 * uint8_t *mem - Array en el que se almacena el comando para enviar comandos y
 *                el comando que se desea enviar
 * uint8_t command - El comando que se desea enviar
 * 
 * Retorna:
 * Nada
 **/
void commandSPS(uint8_t *mem, uint8_t command);


/*void sendMSG(void); void sendMSGVerif(bool verif); 
void readMSG(void); 
void sendVerif(bool verif); 
void go_STANDBY_RF(void);
void go_RX_RF(void);
void Init(void);*/


#endif
