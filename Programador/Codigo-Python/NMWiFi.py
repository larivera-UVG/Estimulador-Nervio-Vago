from tkinter import * #Importamos tkinter para nuestra interfáz gráfica
import socket #Importamos la librería socket para poder comunicarnos con nuestro ESP8266

def enciendeLED():              #Función para encender el LED
    #print("Encendiendo LED")
    
    op1 = cl1.get() # Se obtiene el valor del primer dropdown
    if(op1 == opmodopts[0]): # Se almacena en variable la opcion correspondiente
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
        
        
    s.send(modo.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(ancho.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(time.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(freq.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(sleep.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    
    """
    op1 = cl1.get() # Se obtiene el valor del primer dropdown
    if(op1 == LED1[0]): # Se almacena en variable la opcion correspondiente
        dato = '0'
    elif(op1 == LED1[1]):
        dato = '1'
        
    op2 = cl2.get() # Se obtiene el valor del primer dropdown
    if(op2 == LED2[0]): # Se almacena en variable la opcion correspondiente
        dato2 = '0'
    elif(op2 == LED2[1]):
        dato2 = '1'
        
    op3 = cl3.get() # Se obtiene el valor del primer dropdown
    if(op3 == LED3[0]): # Se almacena en variable la opcion correspondiente
        dato3 = '0'
    elif(op3 == LED3[1]):
        dato3 = '1'
        
    op4 = cl4.get() # Se obtiene el valor del primer dropdown
    if(op4 == LED4[0]): # Se almacena en variable la opcion correspondiente
        dato4 = '0'
    elif(op4 == LED4[1]):
        dato4 = '1'
    
    op5 = cl5.get() # Se obtiene el valor del primer dropdown
    if(op5 == LED5[0]): # Se almacena en variable la opcion correspondiente
        dato5 = '0'
    elif(op5 == LED5[1]):
        dato5 = '1'
    
    s.send(dato.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(dato2.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(dato3.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(dato4.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(dato5.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    """
    
    print("Parámetros enviados")

"""def apagaLED():                #Función para apagar el LED
    print("Apagando LED")
    dato = '0'
    dato2 = '0'
    dato3 = '0'
    dato4 = '0'
    dato5 = '0'
    s.send(dato.encode(encoding='utf_8'))  #Enviamos 0 al modulo ESP
    s.send(dato2.encode(encoding='utf_8'))  #Enviamos 0 al modulo ESP
    s.send(dato3.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(dato4.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
    s.send(dato5.encode(encoding='utf_8'))  #Enviamos 1 al modulo ESP
"""    
    
def cerrar():
    s.close()
    root.destroy()

#Variables para el padding(Espaciado entre objetos) en X e Y
padX=10  
padY=20

ESP_IP = '192.168.0.16'  #IP de nuestro modulo
ESP_PORT = 8266 #Puerto que hemos configurado para que abra el ESP

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #Creamos el objeto socket para conectarnos.

root = Tk() #Creamos la ventana principal de nuestra aplicación
root.title("Controlador ESP8266") #Cambiamos el título a nuestra 

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

# Ubicacion de los botones y label en la interfaz grafica
#button_snd.grid(row=6, column=0) # Fila 1, columna 0
#button_close.grid(row=6, column=2) # Fila 1, columna 2
label1.grid(column = 0, row = 1) # Fila 0, columna 0
label2.grid(column = 0, row = 2) # Fila 0, columna 0
label3.grid(column = 0, row = 3) # Fila 0, columna 0
label4.grid(column = 0, row = 4) # Fila 0, columna 0
label5.grid(column = 0, row = 5) # Fila 0, columna 0


"""
LED1 = ["OFF", "ON"]
LED2 = ["OFF", "ON"]
LED3 = ["OFF", "ON"]
LED4 = ["OFF", "ON"]
LED5 = ["OFF", "ON"]

#frame = Frame (root)  #Creamos el contenedor denuestros objetos

cl1 = StringVar()
cl1.set(LED1[0])

cl2 = StringVar()
cl2.set(LED2[0])

cl3 = StringVar()
cl3.set(LED3[0])

cl4 = StringVar()
cl4.set(LED4[0])

cl5 = StringVar()
cl5.set(LED5[0])

drop1 = OptionMenu(root,cl1,*LED1)
drop1.grid(row=1, column=1,columnspan=2)

drop2 = OptionMenu(root,cl2,*LED2)
drop2.grid(row=2, column=1,columnspan=2)

drop3 = OptionMenu(root,cl3,*LED3)
drop3.grid(row=3, column=1,columnspan=2)

drop4 = OptionMenu(root,cl4,*LED4)
drop4.grid(row=4, column=1,columnspan=2)

drop5 = OptionMenu(root,cl5,*LED5)
drop5.grid(row=5, column=1,columnspan=2)


label1 = Label(root, text = "LED1")
label2 = Label(root, text = "LED2")
label3 = Label(root, text = "LED3")
label4 = Label(root, text = "LED4")
label5 = Label(root, text = "LED5")
"""

# Ubicacion de los botones y label en la interfaz grafica
#button_snd.grid(row=6, column=0) # Fila 1, columna 0
#button_close.grid(row=6, column=2) # Fila 1, columna 2
label1.grid(column = 0, row = 1) # Fila 0, columna 0
label2.grid(column = 0, row = 2) # Fila 0, columna 0
label3.grid(column = 0, row = 3) # Fila 0, columna 0
label4.grid(column = 0, row = 4) # Fila 0, columna 0
label5.grid(column = 0, row = 5) # Fila 0, columna 0


lbl_titulo = Label(root, text="Controlador ESP8266")  #Creamos texto para el título
#imagenESP = PhotoImage(file="esp8266.png") #Cargamos imágen del ESP8266
#lbl_imagen = Label(frame, image=imagenESP) #Creamos etiqueta para poner la foto del ESP8266

lbl_titulo.grid(row=0, column=0, pady=padY,padx=padX)  #Añadimos el título a nuestro contenedor
#lbl_imagen.grid (row=0, column=1,columnspan=2,pady=padY,padx=padX) #Añadimos nuestra imágen al contenedor




lbl_LEDControl = Label (root, text="Control LED") #Texto "Control LED"
lbl_LEDControl.grid (row=8, column=0) # Añadimos el texto "Control LED" al contenedor


    
btn_LEDOn = Button(root, text="ENVIAR", fg="green", command=enciendeLED)  #Creamos botón de encendido del LED
#btn_LEDOff = Button(root, text="Off", fg="red",command=apagaLED)      #Creamos botón de apagado del LED  
btn_LEDOn.grid (row=8, column=1,pady=padY)      #Añadimos el botónd "ON" a nuestro contenedor.                                                 
#btn_LEDOff.grid (row=8, column=2,pady=padY)     #Añadimos el botónd "OFF" a nuestro contenedor. 



btn_Cierre = Button(root, text="Cerrar", fg="black",command=cerrar)      #Creamos botón de apagado del LED  
btn_Cierre.grid (row=9, column=1,pady=padY)      #Añadimos el botónd "ON" a nuestro contenedor.
#frame.pack()

s.connect((ESP_IP , ESP_PORT)) #Nos conectamos a la IP y el puerto que hemos declarado al inicio.


root.mainloop()


