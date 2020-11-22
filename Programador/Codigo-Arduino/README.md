# En este folder están las archivos de Arduino utilizados para pruebas

## Pruebas de interfaz gráfica y envío de parámetros desde ésta | 7 de junio 2020

- BuzzerControl.ino: archivo que lee los valores enviados desde la interfaz gráfica de Python y hace resonar un buzzer a esta frecuencia recibida. Al recibir un cero, se apaga el buzzer. 

## Pruebas de comunicación inalámbrica entre dos Arduinos | 10 de agosto  2020 

- SendTry.ino: recibe los datos desde una terminal serial y los envía al otro Arduino por medio de comunicación inalámrbica
- ReadTry.ino: recibe los datos del otro Arduino y los interpreta para poder modificar los parámetros de un pin PWM. 

## Pruebas de comunicación inalámbrica entre dos Arduinos enviando los parámetros desde Python | 17 de agosto 2020

- PyComTry.ino: recibe los parámetros desde Python, los almacena y los envía a otro Arduino para definir la estimulación 
- PythonReadTry.ino: recibe los parámetros del otro Arduino y se encarga de manejarlos para definir la señal de estimulación. 

## Pruebas de comunicación inalámbrica físicas entre dos Arduinos, utilizando la interfaz gráfica creada en Python | 30 de agosto 2020
- RFSendTry.ino: recibe los parámetros de la interfaz gráfica en Python y los envía por medio de un módulo RF (433 MHz) a otro Arduino.
- RFReceiveTry.ino: recibe los parámetros del otro Arduino con el receptor RF y los interpreta para cambiar los parámetros de una señal PWM. 
- Se eliminaron los archivos BuzzerControl.ino, SendTry.ino y ReadTry.ino pues ya no son utilizados.

## Actualización 22 de noviembre de 2020
- Se eliminaron los archivos PyComTry, PythonReadTry, RFReceiveTry y RFSendTry, ya que no son relevantes para el prototipo actual. 
- NMRecRF.ino: código para el receptor de 433 MHz. El módulo receptor RF, conectado a un Arduino Uno, recibe los parámetros de estimulación y muestra en el monitor serial los parámetros recibidos.
- SPITry: carpeta con la librería para uso del módulo SPSGRF-868. El código para el receptor y el transmisor tienen la misma base debido a que ambos módulos funcionan para ambos casos. 