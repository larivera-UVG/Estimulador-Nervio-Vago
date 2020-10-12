# Módulo Programador

En este repositorio se encuentran los archivos utilizados para implementar el Módulo Programador del proyecto de Neuroestimulación del Nervio Vago trabajado en la Universidad del Valle de Guatemala. 

## Distribución de los Archivos
* [Código de Arduino](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino)

  En esta carpeta se almacenan todos los archivos de Arduino utilizados para pruebas de comunicación serial. Los archivos de Arduino deben ir en carpetas de su mismo nombre y     por eso los archivos están en carpetas distintas dentro de ésta. 

  * [PyComTry](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino/PyComTry)
  * [PythonReadTry](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino/PythonReadTry)
  
      Archivos utilizados para la simulación de comunicación inalámbrica en Proteus. 
      
  * [RFReceiveTry](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino/RFReceiveTry)
  * [RFSendTry](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Arduino/RFSendTry)
  
      Archivos utilizados para comunicación inalámbrica entre dos Arduino Uno física utilizando módulos 433 MHz RF. 
  
* [Código de Python](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python.py)

    En esta carpeta se almacenan los archivos de Python utilizados para envío de datos por WiFi o por comunicación serial. Se genera una interfaz gráfica simple y amigable para     la selección de parámetros de estimulación. 
    
  * [ComAP_GUI](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python/ComAP_GUI.py)
  * [GUI_PP](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python/GUI_PP.py)
  * [NMWiFi](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python/NMWiFi.py)
  * [NewGUI](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python/NewGUI.py)
  * [ProteusCom](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-Python/ProteusCom.py)
  
* [Código de ESP8266](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266)
  
    En esta carpeta se almacenan los archivos de Arduino utilizados para pruebas con el ESP8266. Debido a que se programa desde el IDE de Arduino, los archivos deben en ir en       una carpeta con el mismo nombre.
    
  * [NMRecRF](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266/NMRecRF)
  * [NMTrnsmRF](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266/NMTrnsmRF)
  
      Archivos para replicar lo logrado con los Arduino Uno. Comunicación PC-ESP866 por medio de comunicación serial y para la comunicación inalámbrica se usan los módulos RF de       433 MHz.
      
  * [ESPInt](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266/ESPInt)
  
      Archivo que recibe los parámetros de estimulación por WiFi y no por comunicación serial. 

  * [ESPAll](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Codigo-ESP8266/ESPAll)
  
      Archivo para comunicarse con la PC por medio de WiFi o por comunicación serial. 

  
  
* [Documentación](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación)

    En esta carpeta se encuentra la versión actualizada del trabajo escrito de la tesis (en formato pdf) y la documentación de los componentes utilizados. 
    
  * [Tesis Miguel Alvarez](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Documentación/Tesis%20Miguel%20Alvarez.pdf)
      
      Versión actualizada de tesis. 
  
* [Esquemáticos](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Esquemáticos)

    En esta carpeta se encuentran los archivos de Proteus y Altium utilizados para simulación de circuitos y creación de PCBs.
    
  * [Esquemático de Proteus](https://github.com/larivera-UVG/Estimulador-Nervio-Vago/tree/master/Programador/Esquemáticos/ByteRead.pdsprj)
  
      Esquemático utilizado para la simulación de comunicación inalámbrica entre dos Arduino Uno en Proteus. 
  
