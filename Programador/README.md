# Módulo Programador - Sistema VNS

En este repositorio se encuentran los archivos utilizados para implementar el Módulo Programador del proyecto de Neuroestimulación del Nervio Vago trabajado en la Universidad del Valle de Guatemala. 

## Funcionamiento del Neuroestimulador del Nervio Vago
El Sistema de Neuroestimulación del Nervio Vago (Sistema VNS) se divide en dos módulos principales: Módulo de Estimulación y Módulo Programador. 

### Módulo de Estimulación 
El Módulo de Estimulación se implanta en el área pectoral y, mediante un cable con electrodos, se conecta al nervio vago. Por medio del cable se transmiten pulsos eléctricos al Nervio Vago, que lo estimulan para prevenir y abortar convulsiones epilépticas en camino o en proceso. Este módulo es trabajado por Gustavo Ordoñez y se puede acceder al repositorio en el siguiente [enlace](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Estimulador).

### Módulo Programador
El Módulo Programador sirve para poder comunicar las parámetros de estimulación (corriente de estimulación, tiempo de encendido y apagado, frecuencia de estimulación y ancho de pulso) al Módulo Estimulador. Estos parámetros se programan de forma inalámbrica utilizando módulos de comunicación por radiofrecuencia (RF). Para la programación inalámbrica de los parámetros se utiliza una varilla programadora a la cual se le cargan los parámetros de estimulación por medio de una aplicación (interfaz gráfica) para Windows programada en Python. Esta interfaz gráfica es amigable y fácil de usar para que el personal médico no tenga problemas al utilizarla. La interfaz gráfica puede cargar los parámetros a la varilla por medio de WiFi, y si la conexión no es posible, se puede conectar la varilla a la PC por medio de cable USB para la carga de parámetros. 

![Diagrama de Funcionamiento](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/blob/master/Programador/Im%C3%A1genes/Prototipo%20nRF24L.png)

En este módulo se utilizó el ESP8266 como controlador de la varilla progamadora, para comunicarse con la aplicación de Python, por medio de WiFi o por comunicación serial y  Arduino Uno como simulación del controlador del Módulo Estimulador.

## Manual de Usuario 

En el siguiente [enlace](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/Manual%20de%20Usuario%20-%20Módulo%20de%20Programación%20V%200.1.pdf) se puede encontrar el Manual de Usuario Versión 0.1 para el Módulo de Programación. Este manual muestra la forma de instalación de los archivos y el uso correcto para poder programar los parámetros de estimulación en el generador de pulsos. 

## Distribución de Archivos
* [Código de Arduino](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino)

  En esta carpeta se encuentran los archivos utilizados para simulación del Módulo de Estimulación. Los archivos de Arduino deben ir en carpetas de su mismo nombre y     por eso los archivos están en carpetas distintas dentro de ésta. 

  * [NMRecRF](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino/NMRecRF)

      Archivo utilizado para recibir datos por RF, utilizando el módulo de 433 MHz, e imprimirlos en el monitor serial para verificación.
        
* [Código de Python](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python.py)

    En esta carpeta se almacenan los archivos de Python utilizados para envío de datos por WiFi o por comunicación serial. Se genera una interfaz gráfica simple y amigable para la selección de parámetros de estimulación. 
    
  * [SoftProg](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python/SoftProg.py)
  
* [Código de ESP8266/NodeMcu](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266)
  
    En esta carpeta se almacenan los archivos de Arduino utilizados para pruebas con el ESP8266. Debido a que se programa desde el IDE de Arduino, los archivos deben en ir en una carpeta con el mismo nombre.
    
  * [VarProgCode](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266/VarProgCode)
  
      Carepta con código de la varilla programadora para usarse con el módulo nRF24L01+ y la librería [RF24](http://tmrh20.github.io/RF24/index.html).

* [Documentación](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación)

    En esta carpeta se encuentra la versión actualizada del trabajo escrito de la tesis (en formato pdf), el manual de usuario y la documentación de los componentes utilizados. 
    
  * [Tesis Miguel Alvarez](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/Tesis%20Miguel%20Alvarez.pdf)
      
      Versión actualizada de tesis.     

  * [Manual de Usuario](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/Manual%20de%20Usuario%20-%20Módulo%20de%20Programación%20V%200.1.pdf)
      
      Manual para el uso del Módulo de Programación.

  * [Datasheet nRF24L01+](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/nRF24L01DataSheet.pdf)
      
      Hoja de datos del transceptor nRF24L01+. 

  
* [Esquemáticos](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Esquemáticos)

    En esta carpeta se encuentran los archivos Altium utilizados para simulación de circuitos y creación de PCBs.
    
  * [Conexión RF24-NodeMCU](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/blob/master/Programador/Esquem%C3%A1ticos/nRF24NodeMCU.PNG)
  
      Esquemático de conexión entre módulo nRF24L01+ y NodeMCU. Omitir DHT11 (sensor de temperatura y humedad). [Fuente](https://how2electronics.com/esp8266-nrf24l01-gateway-arduino-node/)

  * [Conexión RF24-Arduino Uno](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/blob/master/Programador/Esquem%C3%A1ticos/nRF24Arduino.PNG)
  
      Placa para el módulo SPSGRF. [Fuente](https://create.arduino.cc/projecthub/muhammad-aqib/nrf24l01-interfacing-with-arduino-wireless-communication-0c13d4)
