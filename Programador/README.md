# Módulo Programador - Sistema VNS

En este repositorio se encuentran los archivos utilizados para implementar el Módulo Programador del proyecto de Neuroestimulación del Nervio Vago trabajado en la Universidad del Valle de Guatemala. 

## Funcionamiento del Neuroestimulador del Nervio Vago
El Sistema de Neuroestimulación del Nervio Vago (Sistema VNS) se divide en dos módulos principales: Módulo de Estimulación y Módulo Programador. 

### Módulo de Estimulación 
El Módulo de Estimulación se implanta en el área pectoral y, mediante un cable con electrodos, se conecta al nervio vago. Por medio del cable se transmiten pulsos eléctricos al Nervio Vago, que lo estimulan para prevenir y abortar convulsiones epilépticas en camino o en proceso. Este módulo es trabajado por Gustavo Ordoñez y se puede acceder al repositorio en el siguiente [enlace](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Estimulador).

### Módulo Programador
El Módulo Programador sirve para poder comunicar las parámetros de estimulación (corriente de estimulación, tiempo de encendido y apagado, frecuencia de estimulación y ancho de pulso) al Módulo Estimulador. Estos parámetros se programan de forma inalámbrica utilizando módulos de comunicación por radiofrecuencia (RF). Para la programación inalámbrica de los parámetros se utiliza una varilla programadora a la cual se le cargan los parámetros de estimulación por medio de una aplicación (interfaz gráfica) para Windows programada en Python. Esta interfaz gráfica es amigable y fácil de usar para que el personal médico no tenga problemas al utilizarla. La interfaz gráfica puede cargar los parámetros a la varilla por medio de WiFi, y si la conexión no es posible, se puede conectar la varilla a la PC por medio de cable USB para la carga de parámetros. 

![Diagrama de Funcionamiento](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Imágenes/Prototipo3.png)

En este módulo se utilizó el ESP8266 como controlador de la varilla progamadora, para comunicarse con la aplicación de Python, por medio de WiFi o por comunicación serial y  Arduino Uno como simulación del controlador del Módulo Estimulador. 

## Distribución de Archivos
* [Código de Arduino](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino)

  En esta carpeta se encuentran los archivos utilizados para simulación del Módulo de Estimulación. Los archivos de Arduino deben ir en carpetas de su mismo nombre y     por eso los archivos están en carpetas distintas dentro de ésta. 

  * [NMRecRF](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino/NMRecRF)

      Archivo utilizado para recibir datos por RF, utilizando el módulo de 433 MHz, e imprimirlos en el monitor serial para verificación.
      
  * [SPITry](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino/SPITry)
  
      Carpeta que implementa la librería para usar el módulo SPSGRF-868 como receptor o como transmisor. 
  
* [Código de Python](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python.py)

    En esta carpeta se almacenan los archivos de Python utilizados para envío de datos por WiFi o por comunicación serial. Se genera una interfaz gráfica simple y amigable para la selección de parámetros de estimulación. 
    
  * [NewGUI](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python/NewGUI.py)
  
* [Código de ESP8266](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266)
  
    En esta carpeta se almacenan los archivos de Arduino utilizados para pruebas con el ESP8266. Debido a que se programa desde el IDE de Arduino, los archivos deben en ir en una carpeta con el mismo nombre.
    
  * [ESPAll](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266/ESPAll)
  
      Archivo para comunicarse con la PC por medio de WiFi o por comunicación serial. 

  * [SPITry](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266/SPITry)
  
      Carpeta que implementa la librería para usar el módulo SPSGRF-868 como receptor o como transmisor.

* [Documentación](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación)

    En esta carpeta se encuentra la versión actualizada del trabajo escrito de la tesis (en formato pdf), el manual de usuario y la documentación de los componentes utilizados. 
    
  * [Tesis Miguel Alvarez](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/Tesis%20Miguel%20Alvarez.pdf)
      
      Versión actualizada de tesis.     

  * [Manual de Usuario](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/Manual%20de%20Usuario%20-%20Módulo%20de%20Programación%20V%200.1.pdf)
      
      Manual para el uso del Módulo de Programación.

  * [Datasheet SPSGRF](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/SPSGRF.pdf)
      
      Hoja de datos del módulo RF utilizado en este proyecto. 

  * [Datasheet SPIRIT1](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/Tesis%20Miguel%20Alvarez.pdf)
      
      Hoja de datos del transreceptor sub-1GHZ que contiene el módulo SPSGRF. 

  
* [Esquemáticos](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Esquemáticos)

    En esta carpeta se encuentran los archivos Altium utilizados para simulación de circuitos y creación de PCBs.
    
  * [Esquemático SPSGRF](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Esquemáticos/SPSGRFSheet.SchDoc)
  
      Esquemático de conexión para la placa SPSGRF. 

  * [Placa SPSGRF](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Esquemáticos/SPSGRFpcb.PcbDoc)
  
      Placa para el módulo SPSGRF. 
