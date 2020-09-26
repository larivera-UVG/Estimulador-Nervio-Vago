"""
NMWiFi.py

Basado en el código de TutoElectro: Tutorial_ESP8266_Python_1
Canal de youtube: https://www.youtube.com/c/Tutoelectro1/featured

Miguel Alfonso Alvarez Sierra - 16168
Ingeniería Mecatrónica - UVG
"""

#*****************************************************************************
# LIBRERIAS UTILIZADAS
#*****************************************************************************

from tkinter import * # Librería para crear la interfaz gráfica
import socket # Librería socket para poder comunicarse con el ESP8266 por medio de WiFi

#*****************************************************************************
# FUNCIONES UTILIZADAS
#*****************************************************************************

def parSend(): # Función para enviar los parámetros por medio de WiFi
    
    op1 = cl1.get() # Se obtiene el valor del primer dropdown
    if(op1 == opmodopts[0]): # Se almacena en variable la opción correspondiente
        modo = '1'
    elif(op1 == opmodopts[1]):
        modo = '2'
    elif(op1 == opmodopts[2]):
        modo = '3'
        
    op2 = cl2.get()
    if(op2 == anchopts[0]):
        ancho = '1'
    elif(op2 == anchopts[1]):
        ancho = '2'
    elif(op2 == anchopts[2]):
        ancho = '3'
    elif(op2 == anchopts[3]):
        ancho = '4'
    elif(op2 == anchopts[4]):
        ancho = '5'
        
    op3 = cl3.get()
    if(op3 == timeopts[0]):
        time = '1'
    elif(op3 == timeopts[1]):
        time = '2'
    elif(op3 == timeopts[2]):
        time = '3'
    elif(op3 == timeopts[3]):
        time = '4'
    elif(op3 == timeopts[4]):
        time = '5'
        
    op4 = cl4.get()
    if(op4 == freqopts[0]):
        freq = '1'
    elif(op4 == freqopts[1]):
        freq = '2'
    elif(op4 == freqopts[2]):
        freq = '3'
    elif(op4 == freqopts[3]):
        freq = '4'
    elif(op4 == freqopts[4]):
        freq = '5'
    elif(op4 == freqopts[5]):
        freq = '6'
    elif(op4 == freqopts[6]):
        freq = '7'
    elif(op4 == freqopts[7]):
        freq = '8'
        
    op5 = cl5.get()
    if(op5 == sleepopts[0]):
        sleep = '1'
    elif(op5 == sleepopts[1]):
        sleep = '2'
        
    
    # Se envían los parámetros por medio de WiFi al ESP8266
    s.send(modo.encode(encoding='utf_8'))  
    s.send(ancho.encode(encoding='utf_8'))  
    s.send(time.encode(encoding='utf_8'))
    s.send(freq.encode(encoding='utf_8'))  
    s.send(sleep.encode(encoding='utf_8'))
        
    print("Parámetros enviados") # Se muestra en la consola la confirmación del
                                # envío de parámetros
    
def cerrar(): # Función para cerrar completamente la GUI
    s.close() # Se cierra el socket
    root.destroy() # Se destruye (cierra) la interfaz gráfica

# Variables para definir el espacio entre objetos en X y en Y (padding)
padX=10  
padY=20

ESP_IP = '192.168.0.16' # Se indica la IP a la que se quiere conectar (la del ESP8266)
ESP_PORT = 8266 # Puerto en el que se abrirá la comunicación

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Creación del objeto socket

root = Tk() # Se define la ventana de la interfaz gráfica 
root.title("Controlador ESP8266") # Se titula a la ventana del GUI  

# Listas utilizadas para los dropdown boxes
anchopts = ["25%", "30%", "50%", "75%", "100%"]
freqopts = ["490.20 Hz", "30.64 Hz", "122.50 Hz", "245.10 Hz", 
            "980.39 Hz", "3921.16 Hz", "31372.55 Hz", "Frecuencia 8"]
opmodopts = ["Modo 1", "Modo 2", "Modo 3"]
timeopts = ["Tiempo 1", "Tiempo 2", "Tiempo 3", "Tiempo 4", "Tiempo 5"]
sleepopts = ["Sleep 1", "Sleep 2"]

# DEFINICION DE BOTONES Y ENTRY BOX
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

label1 = Label(root, text = "Modo de Operación: ")
label2 = Label(root, text = "Ancho de pulso: ")
label3 = Label(root, text = "Tiempo: ")
label4 = Label(root, text = "Frecuencia: ")
label5 = Label(root, text = "Tiempo de sleep: ")

label1.grid(column = 0, row = 1) # Fila 1, columna 0
label2.grid(column = 0, row = 2) # Fila 2, columna 0
label3.grid(column = 0, row = 3) # Fila 3, columna 0
label4.grid(column = 0, row = 4) # Fila 4, columna 0
label5.grid(column = 0, row = 5) # Fila 5, columna 0

lbl_titulo = Label(root, text="Envío de Parámetros") # Texto del título

lbl_titulo.grid(row=0, column=0, pady=padY,padx=padX) # Se añade el título al contenedor

lbl_LEDControl = Label (root, text="Control parámetros") # Texto de envío
lbl_LEDControl.grid (row=8, column=0) # Añadimos el texto "Control LED" al contenedor

btn_LEDOn = Button(root, text="ENVIAR", fg="green", command=enciendeLED) # Botón para envío
btn_LEDOn.grid (row=8, column=1,pady=padY) # Ubicación del botón                                                    

btn_Cierre = Button(root, text="Cerrar", fg="black",command=cerrar) # Botón para cerrar la interfaz  
btn_Cierre.grid (row=9, column=1,pady=padY) # Ubicación del botón

s.connect((ESP_IP , ESP_PORT)) # Se conecta Python a la IP y al puerto definidos

root.mainloop()


