#!/usr/bin/python


import sys, tty, termios, pyfirmata

board = pyfirmata.Arduino('/dev/ttyACM0')


pinRotorDerechoAdelante = board.get_pin('d:11:o')
pinRotorDerechoPatras = board.get_pin('d:10:o')
pinRotorIzquierdoAdelante = board.get_pin('d:3:p')
pinRotorIzquierdoPatras = board.get_pin('d:9:p')
x = board.get_pin('d:6:s')
y = board.get_pin('d:5:s')

centrox = 70
centroy = 160
x.write(centrox)
y.write(centroy)






def read_ch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch



while True:
    ch = read_ch()
    if ch == 'v':
        velocidads = raw_input('Introduzca la velocidad de 0 a 100:')
        velocidad = int(velocidads)
        
    if ch == 'w':
        print('Hacia delante')
        pinRotorIzquierdoPatras.write(0)
        pinRotorDerechoPatras.write(0)
        pinRotorIzquierdoAdelante.write(1)
        pinRotorDerechoAdelante.write(1)
               
    if ch == 's':
        print('Hacia atras')
        pinRotorIzquierdoAdelante.write(0)
        pinRotorDerechoAdelante.write(0)
        pinRotorIzquierdoPatras.write(1)
        pinRotorDerechoPatras.write(1)
        
    if ch == 'n':
        print('Punto muerto')

        pinRotorIzquierdoPatras.write(0)
        pinRotorDerechoPatras.write(0)
        pinRotorIzquierdoAdelante.write(0)
        pinRotorDerechoAdelante.write(0)
                       
    if ch == 'a':
        print('Gira izquierda')

        pinRotorDerechoPatras.write(0)
        pinRotorIzquierdoAdelante.write(0)
        pinRotorIzquierdoPatras.write(0)
        pinRotorDerechoAdelante.write(1)
               
      
        
    if ch == 'd':
        print('Gira derecha')
        
        pinRotorIzquierdoPatras.write(0)
        pinRotorDerechoAdelante.write(0)
        pinRotorDerechoPatras.write(0)
        pinRotorIzquierdoAdelante.write(1)
               
      

        
    if ch == 'e':
        print('Voltea camara derecha')
        if centrox >= 10:
            centrox = centrox - 5
            x.write(centrox)
        else :
            print('No se puede girar mas la camara a la derecha')

    if ch == 'q':
        print('Voltea camara izquierda')
        if centrox <= 170:
            centrox = centrox + 5
            x.write(centrox)
        else :
            print('No se puede girar mas la camara a la izquierda')

    if ch == 'f':
        print('Voltea camara derecha')
        if centroy >= 10:
            centroy = centroy - 5
            y.write(centroy)
        else :
            print('No se puede girar mas la camara a la derecha')

    if ch == 'r':
        print('Voltea camara izquierda')
        if centroy <= 170:
            centroy = centroy + 5
            y.write(centroy)
        else :
            print('No se puede girar mas la camara a la izquierda')



    if ch == '0':
        break
