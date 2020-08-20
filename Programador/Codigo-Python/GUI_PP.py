"""
GUI_PP.py


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
ser = serial.Serial('COM2', 115200) # Comunicacion serial al puerto 3 (COM3)

#*****************************************************************************
# FUNCIONES DEFINIDAS
#*****************************************************************************

#def send_val():
    
def send_par(): # Funcion para el boton que envia las frecuencias a Arduino
    
    op1 = cl1.get()
    if(op1 == opmodopts[0]):
        modo = 1
    elif(op1 == opmodopts[1]):
        modo = 2
    elif(op1 == opmodopts[2]):
        modo = 3
        
    op2 = cl2.get()
    if(op2 == anchopts[0]):
        ancho = 1
    elif(op2 == anchopts[1]):
        ancho = 2
    elif(op2 == anchopts[2]):
        ancho = 3
    elif(op2 == anchopts[3]):
        ancho = 4
    elif(op2 == anchopts[4]):
        ancho = 5
        
    op3 = cl3.get()
    if(op3 == timeopts[0]):
        time = 1
    elif(op3 == timeopts[1]):
        time = 2
    elif(op3 == timeopts[2]):
        time = 3
    elif(op3 == timeopts[3]):
        time = 4
    elif(op3 == timeopts[4]):
        time = 5
        
    op4 = cl4.get()
    if(op4 == freqopts[0]):
        freq = 1
    elif(op4 == freqopts[1]):
        freq = 2
    elif(op4 == freqopts[2]):
        freq = 3
    elif(op4 == freqopts[3]):
        freq = 4
    elif(op4 == freqopts[4]):
        freq = 5
    elif(op4 == freqopts[5]):
        freq = 6
    elif(op4 == freqopts[6]):
        freq = 7
    elif(op4 == freqopts[7]):
        freq = 8
        
    op5 = cl5.get()
    if(op5 == sleepopts[0]):
        sleep = 1
    elif(op5 == sleepopts[1]):
        sleep = 2
    elif(op5 == sleepopts[2]):
        sleep = 3
        
    
    ser.write(str(modo).encode()) # Se envia el valor a Arduino
    ser.write(str(ancho).encode()) # Se envia el valor a Arduino
    ser.write(str(time).encode()) # Se envia el valor a Arduino
    ser.write(str(freq).encode()) # Se envia el valor a Arduino
    ser.write(str(sleep).encode()) # Se envia el valor a Arduino
    
    
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


anchopts = ["25%", "30%", "50%", "75%", "100%"]
freqopts = ["490.20 Hz", "30.64 Hz", "122.50 Hz", "245.10 Hz", 
            "980.39 Hz", "3921.16 Hz", "31372.55 Hz", "Frecuencia 8"]
opmodopts = ["Modo 1", "Modo 2", "Modo 3"]
timeopts = ["Tiempo 1", "Tiempo 2", "Tiempo 3", "Tiempo 4", "Tiempo 5"]
sleepopts = ["Sleep 1", "Sleep 2"]

cl1 = StringVar()
cl1.set(opmodopts[0])

cl2 = StringVar()
cl2.set(anchopts[0])

cl3 = StringVar()
cl3.set(timeopts[0])

cl4 = StringVar()
cl4.set(freqopts[0])

cl5 = StringVar()
cl5.set(sleepopts[0])

drop1 = OptionMenu(root,cl1,*opmodopts)
drop1.grid(row=1, column=1,columnspan=2)

drop2 = OptionMenu(root,cl2,*anchopts)
drop2.grid(row=2, column=1,columnspan=2)

drop3 = OptionMenu(root,cl3,*timeopts)
drop3.grid(row=3, column=1,columnspan=2)

drop4 = OptionMenu(root,cl4,*freqopts)
drop4.grid(row=4, column=1,columnspan=2)

drop5 = OptionMenu(root,cl5,*sleepopts)
drop5.grid(row=5, column=1,columnspan=2)

# Boton para enviar frecuencias a Arduino
button_snd = Button(root, text="SEND",padx=40, pady=20, command=send_par)

# Boton para cerrar todo
button_close = Button(root, text="QUIT",padx=40, pady=20, command=clear_all)
# Texto que dice "Frecuencia
label1 = Label(root, text = "Modo de Operación: ")
label2 = Label(root, text = "Ancho de pulso: ")
label3 = Label(root, text = "Tiempo: ")
label4 = Label(root, text = "Frecuencia: ")
label5 = Label(root, text = "Tiempo de sleep: ")

# Ubicacion de los botones y label en la interfaz grafica
button_snd.grid(row=6, column=0) # Fila 1, columna 0
button_close.grid(row=6, column=2) # Fila 1, columna 2
label1.grid(column = 0, row = 1) # Fila 0, columna 0
label2.grid(column = 0, row = 2) # Fila 0, columna 0
label3.grid(column = 0, row = 3) # Fila 0, columna 0
label4.grid(column = 0, row = 4) # Fila 0, columna 0
label5.grid(column = 0, row = 5) # Fila 0, columna 0


root.mainloop() # Se crea la interfaz con todo lo definido