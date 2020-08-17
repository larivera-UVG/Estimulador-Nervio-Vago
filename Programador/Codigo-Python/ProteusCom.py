import serial

ser = serial.Serial("COM2", 115200)

outcon = True


opmod = input("Modo de operacion: ")
ancho = input("Ancho de pulso: ")
tiempo = input("Tiempo de estimulacion: ")
freq = input("Frecuencia: ")
sleep = input("Tiempo sleep: ")


while(outcon == True):
    ser.write(str(opmod).encode())
    ser.write(str(ancho).encode())
    ser.write(str(tiempo).encode())
    ser.write(str(freq).encode())
    ser.write(str(sleep).encode())
    print("")
    print("Parámetros enviados")
    
    dec = input("Desea continuar? (s/n): ")
    if(str(dec) == 'n'):
        outcon = False
        ser.close()
    else: 
        opmod = input("Modo de operacion: ")
        ancho = input("Ancho de pulso: ")
        tiempo = input("Tiempo de estimulacion: ")
        freq = input("Frecuencia: ")
        sleep = input("Tiempo sleep: ")



