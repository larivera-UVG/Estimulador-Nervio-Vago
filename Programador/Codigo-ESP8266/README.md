# En este folder están las archivos de Arduino utilizados para pruebas con el ESP8266

## Pruebas de interfaz gráfica y envío de parámetros desde ésta con módulos RF 433 MHz físicos | 22 de septiembre 2020
- NMTrnsmRF.ino: código para el transmisor. El NodeMcu se conecta con la computadora y recibe los parámetros de estimulación desde la interfaz gráfica de Python. Al recibir los parámetros los envía al módulo receptor RF.
- NMRecRF.ino: código para el receptor. El módulo receptor RF, conectado a un Arduino Uno, recibe los parámetros de estimulación y muestra en el monitor serial los parámetros recibidos. 

## Pruebas iguales a la anterior, pero esta vez utilizando WiFi en vez de Comunicación Serial | 26 de septiembre de 2020
- ESPInt.ino: se conecta a la red WiFi como cliente utilizando el protocolo TCP y recibe los parámetros por medio de éste. Luego de recibir los parámetros, se envían por medio de los módulos RF al Arduino Uno. 

## Soporte para comunicación por WiFi o por comunicación serial | 29 de septiembre de 2020
- ESPAll.ino: se intenta conectar el ESP8266 a la red WiFi. Si la conexión es exitosa, se prepara para recibir los parámetros por medio de WiFi. Si la conexión no fue exitosa, se prepara para recibir los parámetros por medio del cable USB (comunicación serial). 
