# En este folder están los archivos asociados al Programador

## Pruebas de interfaz gráfica y envío de parámetros desde ésta | 7 de junio de 2020
- ComAP_GUI.py: archivo de Python en el que se realizó la interfaz gráfica. Desde ésta se pueden enviar frecuencias a Arduino para que haga resonar el buzzer a los diferentes valores que se le envían. 

- BuzzerControl.ino: archivo de Arduino que lee los valores enviados desde la interfaz gráfica de Python y hace resonar un buzzer a esta frecuencia recibida. Al recibir un cero, se apaga el buzzer. 
