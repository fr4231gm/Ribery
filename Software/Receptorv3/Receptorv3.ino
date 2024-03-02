/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

int motorA_adelante = 6;
int motorA_atras = 5;
int motorB_adelante = 3;
int motorB_atras = 7;

int pinLuces = 36;
int pinClaxon = 37;
int pinServoX = 2;
int pinServoY = 8;

Servo servoX;
Servo servoY;

struct package {
  int valorMotorA = 0;
  int valorMotorB = 0;
  int servoX = 90;
  int servoY = 90;
  boolean lightActivated = false;
  boolean claxon = false;
  //Modos de control: (un int por si se crean mas modos de control a futuro)
  //1 - Control básico: Se usan ambos joysticks para dirigir cada uno de los railes del vehiculo
  //2 - Control con controles de cámara: Se usa el joystick izquierdo para controlar el tanque y el derecho para controlar la cámara
  int controlMode = 1;
};
typedef struct package Package;
Package data;


void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando pines de motores");
  servoX.attach(pinServoX);
  servoY.attach(pinServoY);
  pinMode(pinLuces, OUTPUT);
  delay(400);
  //Motor izquierda
  //IN1
  pinMode(6, OUTPUT);
  //IN2
  pinMode(5, OUTPUT);
  //EN
  pinMode(13, OUTPUT);
  //Motor derecha
  //IN3
  pinMode(3, OUTPUT);
  //IN4
  pinMode(7, OUTPUT);
  //ENABLE
  pinMode(11, OUTPUT);

  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);

  Serial.println("Inicializando radio");

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  Serial.println("Comunication address: 00001");
  delay(400);
  Serial.println("Power Leveol: " + RF24_PA_MAX);
  servoX.write(90);
  servoY.write(90);
  delay(400);
  Serial.println("Bienvendio");
  delay(200);
  Serial.println("Sistema inicializado");
}
void loop() {

  if (radio.available()) {
    Serial.println("Conexión establecida");
    while (radio.available()) {
      radio.read(&data, sizeof(data));

    

    if (data.valorMotorA != 0 || data.valorMotorB != 0) {

      if (data.valorMotorA < 0) {
        //Movimiento negativo, lo que indica que vamos marcha atrás
        digitalWrite(motorA_adelante, LOW);
        analogWrite(motorA_atras, abs(data.valorMotorA));
      } else if (data.valorMotorA > 0) {
        digitalWrite(motorA_atras, LOW);
        analogWrite(motorA_adelante, data.valorMotorA);
      } else {
        digitalWrite(motorA_adelante, LOW);
        digitalWrite(motorA_atras, LOW);
      }

      if (data.valorMotorB < 0) {
        //Movimiento negativo, lo que indica que vamos marcha atrás
        digitalWrite(motorB_adelante, LOW);
        analogWrite(motorB_atras, abs(data.valorMotorB));
      } else if (data.valorMotorB > 0) {
        digitalWrite(motorB_atras, LOW);
        analogWrite(motorB_adelante, data.valorMotorB);
      } else {
        digitalWrite(motorB_adelante, LOW);
        digitalWrite(motorB_adelante, LOW);
      }

    } else {
      //No hay velocidades en los joysticks, todo está parado
      digitalWrite(motorA_adelante, LOW);
      digitalWrite(motorA_atras, LOW);
      digitalWrite(motorB_adelante, LOW);
      digitalWrite(motorB_atras, LOW);
    }

    if(data.controlMode == 2){
      servoX.write(data.servoX);
      servoY.write(data.servoY);
    }

    if(data.claxon == true){
      digitalWrite(pinClaxon, HIGH);
    }else{
      digitalWrite(pinClaxon, LOW);
    }

    if(data.lightActivated == true){
      digitalWrite(pinLuces, HIGH);
    }else {
      digitalWrite(pinLuces, LOW);
    }

    delay(50);
    }
  }
}
