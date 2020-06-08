"""
ComAP_GUI.py
Archivo para comunicar Python y Arduino por medio de una interfaz gráfica que
envía diferentes frecuencias a un buzzer

Miguel Alfonso Alvarez Sierra - 16168
Ingeniería Mecatrónica - UVG
"""

#*****************************************************************************
# LIBRERIAS UTILIZADAS
#*****************************************************************************
from tkinter import * # Libreria para interfaz grafica 
import serial # Libreria para comunicacion serial 
 
#*****************************************************************************
# CONEXION CON ARDUINO
#*****************************************************************************
ser = serial.Serial('COM3', 9600) # Comunicacion serial al puerto 3 (COM3)

#*****************************************************************************
# FUNCIONES DEFINIDAS
#*****************************************************************************
def send_freq(): # Funcion para el boton que envia las frecuencias a Arduino
    var = e.get() # Se guarda el valor del entry box en var
    ser.write(str(var).encode()) # Se envia el valor a Arduino
    label2 = Label(root, text = "Frecuencia enviada: " + var) 
    # Se escribe la frecuencia enviada en la interfaz grafica
    label2.grid(column = 4, row = 0) # Se muestra en la columna 4, fila 0
    e.delete(0,END) # Se borra el valor escrito luego de enviarlo 
    
def stop_freq(): # Funcion para el boton que apaga el buzzer
    ser.write(str(0).encode()) # Se envia 0 al buzzer para apagarlo
    
def clear_all(): # Funcion para el boton que cierra el puerto y la ventana de
    # la interfaz grafica
    ser.close() # Se cierra el puerto serial
    root.destroy() # Se cierra la ventana de interfaz grafica

#*****************************************************************************
# INTERFAZ GRAFICA
#*****************************************************************************
root = Tk() # Se define la ventana de interfaz grafica
root.title("Envío de Parámetros") # Se titula a la ventana del GUI

# DEFINICION DE BOTONES Y ENTRY BOX

e = Entry(root, width=40, borderwidth=15) # Entry box 
e.pack()
e.grid(row=0, column=1,columnspan=2) # En la fila 0 y columna 1

# Boton para enviar frecuencias a Arduino
button_snd = Button(root, text="SEND",padx=40, pady=20, command=send_freq)
# Boton para detener el buzzer
button_stop = Button(root, text="STOP",padx=40, pady=20, command=stop_freq)
# Boton para cerrar todo
button_close = Button(root, text="QUIT",padx=40, pady=20, command=clear_all)
# Texto que dice "Frecuencia
label1 = Label(root, text = "Frecuencia: ")

# Ubicacion de los botones y label en la interfaz grafica
button_snd.grid(row=1, column=0) # Fila 1, columna 0
button_stop.grid(row=1, column=1) # Fila 1, columna 1
button_close.grid(row=1, column=2) # Fila 1, columna 2
label1.grid(column = 0, row = 0) # Fila 0, columna 0

root.mainloop() # Se crea la interfaz con todo lo definido