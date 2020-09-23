# En este folder están las archivos de Arduino utilizados para pruebas con el ESP8266

## Pruebas de interfaz gráfica y envío de parámetros desde ésta con módulos RF 433 MHz físicos | 22 de septiembre 2020
- NMTrnsmRF: código para el transmisor. El NodeMcu se conecta con la computadora y recibe los parámetros de estimulación desde la interfaz gráfica de Python. Al recibir los parámetros los envía al módulo receptor RF.
- NMRecRF: código para el receptor. El módulo receptor RF, conectado a un Arduino Uno, recibe los parámetros de estimulación y muestra en el monitor serial los parámetros recibidos. 
