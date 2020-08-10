# En este folder están las archivos de Arduino utilizados para pruebas

## Pruebas de interfaz gráfica y envío de parámetros desde ésta | 7 de junio 2020

- BuzzerControl.ino: archivo que lee los valores enviados desde la interfaz gráfica de Python y hace resonar un buzzer a esta frecuencia recibida. Al recibir un cero, se apaga el buzzer. 

## Pruebas de comunicación inalámbrica entre dos Arduinos | 10 de agosto de 2020 

- SendTry.ino: recibe los datos desde una terminal serial y los envía al otro Arduino por medio de comunicación inalámrbica
- ReadTry.ino: recibe los datos del otro Arduino y los interpreta para poder modificar los parámetros de un pin PWM. 

