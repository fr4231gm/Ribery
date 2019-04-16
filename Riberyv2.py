# -*- coding: iso-8859-15 -*-
import sys, tty, termios
import RPi.GPIO as GPIO
import Adafruit_DHT
import time






trigger_pin = 18
echo_pin = 23
GPIO.setmode(GPIO.BCM)
GPIO.setup(trigger_pin, GPIO.OUT)
GPIO.setup(echo_pin, GPIO.IN)
GPIO.setup(18, GPIO.OUT) #MotorIzqAdelante
GPIO.setup(22, GPIO.OUT) #MotorDchAdelante
GPIO.setup(23, GPIO.OUT) #MotorIzqAtrás
GPIO.setup(24, GPIO.OUT) #MotorDchAtrás
GPIO.setup(5, GPIO.OUT) #LED1
GPIO.setup(6, GPIO.OUT) #LED2

def send_trigger_pulse():
    GPIO.output(trigger_pin, True)
    time.sleep(0.0001)
    GPIO.output(trigger_pin, False)

def wait_for_echo(value,timeout):
    count = timeout
    while GPIO.input(echo_pin) != value and count > 0:
        count = count - 1
def get_distance():
    send_trigger_pulse()
    wait_for_echo(True, 10000)
    start = time.time()
    wait_for_echo(False, 10000)
    finish = time.time()
    pulse_len = finish - start
    distance_cm = pulse_len /0.000058
    distance_in = distance_cm / 2.5
    return(distance_cm, distance_in)


def encenderLuces():
    GPIO.output(5, True)
    GPIO.output(6, True)

def apagarLuces():
    GPIO.output(5, False)
    GPIO.output(6, False)

def read_ch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

def temperatura():
    humedad, temperatura = Adafruit_DHT.read_retry(sensor, pin)
    return humedad, temperatura

    
    


while True:
    ch = read_ch()
    if ch == 'w':
        print('Hacia delante')


        GPIO.output(24, False)
        GPIO.output(18, False)
        GPIO.output(22, True)        
        GPIO.output(23, True)
               
    if ch == 's':
        print('Hacia atras')

        GPIO.output(22, False) 
        GPIO.output(23, False)
        GPIO.output(24, True)
        GPIO.output(18, True)
        
    if ch == 'n':
        print('Punto muerto')


        GPIO.output(18, False)
        GPIO.output(22, False) 
        GPIO.output(23, False)
        GPIO.output(24, False)
                       
    if ch == 'a':
        print('Gira izquierda')


        GPIO.output(23, False)

        GPIO.output(24, False)
        GPIO.output(18, False)
        GPIO.output(22, True) 
        
        
               
    if ch == 'd':
        print('Gira derecha')


        GPIO.output(22, False) 
        GPIO.output(24, False)        
        GPIO.output(18, False)
        GPIO.output(23, True)


    if ch == 'l':
        print('Luces encendidas')
        encenderLuces()

    if ch == 'o':
        print('Luces apagadas')
        apagarLuces()

    if ch == 'm':
        sensor = Adafruit_DHT.DHT22
        humedad, temperatura = Adafruit_DHT.read_retry(sensor, 4)
        print('Humedad: ', humedad, 'Temperatura:', temperatura)


    if ch == 'p':
        print('cm=%f\tinches=%f' %get_distance())
    

        
       
      

    


    if ch == '0':
        GPIO.cleanup()
        break
