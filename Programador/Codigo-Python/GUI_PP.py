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
import serial.tools.list_ports # Modulo para poder ver los puertos seriales

#*****************************************************************************
# FUNCIONES PARA PUERTO SERIAL
#*****************************************************************************

def get_ports(): # Funcion para ver los puertos activos
    ports = serial.tools.list_ports.comports() # Ports guarda la lista de puertos
    # activos
    return ports

def findArduino(portsFound): # Funcion para buscar al Arduino en los puertos
    commPort = 'None' # Condicion para errores
    numConnection = len(portsFound) # Numero de puertos activos 
    
    for i in range(0, numConnection): #Buscar en todos los puertos activos
        port = foundPorts[i] # Tomar el puerto que coincide con el contador
        strPort = str(port) # Convertir su nombre a string
        
        if 'Arduino' in strPort: # Se busca la palabra Arduino en el string
            splitPort = strPort.split(' ') #Se separa el string en los espacios
            commPort = (splitPort[0]) # Se guarda el puerto donde se encuentra 
            # el Arduino
            # Arduino aparece como COMX - Arduino Uno (COM3), lo que nos interesa
            # es el COMX por eso tomamos el espacio 0 del string divido, lo que
            # corresponde a COMX
    
    return commPort # Se retornoa el puerto del Arduino

#*****************************************************************************
# CONEXION CON ARDUINO
#*****************************************************************************
foundPorts = get_ports() # Se obtienen los puertos disponibles
connectPort = findArduino(foundPorts) # Se busca el puerto del Arduino

if connectPort != 'None': # Si se encontro el puerto
    ser = serial.Serial(connectPort, 115200) # Nos conectamos a este
    print('Connected to' + connectPort)
else:
    print('Error de conexion, revisar')

#ser = serial.Serial('COM2', 115200) # Comunicacion serial al puerto 3 (COM3)
#ser = serial.Serial('COM3', 115200) # Comunicacion serial al puerto 3 (COM3)

#*****************************************************************************
# FUNCIONES DEFINIDAS PARA GUI
#*****************************************************************************
def send_par(): # Funcion para el boton que envia los parametros seleccionados
    #en la interfaz a Arduino
    
    op1 = cl1.get() # Se obtiene el valor del primer dropdown
    if(op1 == opmodopts[0]): # Se almacena en variable la opcion correspondiente
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
        
    
    ser.write(str(modo).encode()) # Se envia el valor a Arduino
    ser.write(str(ancho).encode()) # Se envia el valor a Arduino
    ser.write(str(time).encode()) # Se envia el valor a Arduino
    ser.write(str(freq).encode()) # Se envia el valor a Arduino
    ser.write(str(sleep).encode()) # Se envia el valor a Arduino
    
    
def clear_all(): # Funcion para el boton que cierra el puerto y la ventana de
    # la interfaz grafica
    ser.close() # Se cierra el puerto serial
    root.destroy() # Se cierra la ventana de interfaz grafica

#def on_closing(): # Funcion para cerrar el puerto serial y la interfaz gráfica
    # cuando se presiona la X, no necesaria para app 
#    if messagebox.askokcancel("Quit", "Desea salir?"): 
#        clear_all()
    
    
#*****************************************************************************
# INTERFAZ GRAFICA
#*****************************************************************************
root = Tk() # Se define la ventana de interfaz grafica
root.title("Envío de Parámetros") # Se titula a la ventana del GUI

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

# Boton para enviar parametros a Arduino
button_snd = Button(root, text="SEND",padx=40, pady=20, command=send_par)

# Boton para cerrar todo
button_close = Button(root, text="QUIT",padx=40, pady=20, command=clear_all)


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

#root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop() # Se crea la interfaz con todo lo definido