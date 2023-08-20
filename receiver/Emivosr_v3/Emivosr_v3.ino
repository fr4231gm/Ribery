/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

//Valores para los joysticks y declaración de variables

int pinAEjeY = A0;
int pinAEjeX = A1;
int pinBEjeX = A2;
int pinBEjeY = A3;
int joystickA_X = 0;
int joystickA_Y = 0;
int joystickB_X = 0;
int joystickB_Y = 0;
int basicControl = 1;
int cameraControl = 2;
int pinLuces = 2;
int pinClaxon = 3;
int pinCambiarModo = 4;



struct package {
  float valorMotorA = 0.0;
  float valorMotorB = 0.0;
  float servoX = 0.0;
  float servoY = 0.0;
  boolean lightActivated = false;
  boolean claxon = false;
  //Modos de control: (un int por si se crean mas modos de control a futuro)
  //1 - Control básico: Se usan ambos joysticks para dirigir cada uno de los railes del vehiculo
  //2 - Control con controles de cámara: Se usa el joystick izquierdo para controlar el tanque y el derecho para controlar la cámara
  int controlMode = 1;
  typedef struct package Package;
  Package data;




  void setup() {
    Serial.begin(9600);
    radio.begin();
    delay(1000);
    Serial.println("Inicializando sistema de transmisión");
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();
    Serial.println("Comunication address: 00001");
    delay(400);
    Serial.println("Power Level: " + RF24_PA_HIGH);
    delay(400);
    Serial.println("Bienvendio");
    delay(200);
    Serial.println("Sistema inicializado");
  }
  void loop() {

    //Se leen los valores de ambos joysticks
    joystickA_X = analogRead(pinAEjeX);
    joystickA_Y = analogRead(pinAEjeY);
    joystickB_X = analogRead(pinBEjeX);
    joystickB_Y = analogRead(pinBEjeY);

    if (controlMode == basicControl) {
      //En este modo de control directamente calculamos el valor asociado al motor izquierdo y derecho a partir de los valores de Y de los Joysticks
      //El punto de pivote es entre 462 y 562, si el joystick se encuentra entre esos valores, estamos en 0

      //Controles para el Motor A (motor izquierdo)
      if (joystickA_Y > 562) {
        //Motor A hacia delante
        data.valorMotorA = ((joystickA_Y - 562) * 2.216) / 4;
      } else if (joystickA_Y < 462) {
        //Motor A hacia atrás
        data.valorMotorA = -((joystickA_Y - 462) * 2.216) / 4;
      } else if (joystickA_Y > 462 && joystickA_Y < 562) {
        //Motor A parado
        data.valorMotorA = 0.0;
      }

      //Controles para el Motor B (motor derecho)
      if (joystickB_Y > 562) {
        //Motor B hacia delante
        data.valorMotorB = ((joystickB_Y - 562) * 2.216) / 4;
      } else if (joystickB_Y < 462) {
        //Motor B hacia atrás
        data.valorMotorB = -((joystickB_Y - 462) * 2.216) / 4;
      } else if (joystickB_Y > 462 && joystickB_Y < 562) {
        //Motor B parado
        data.valorMotorB = 0.0;
      }



    } else if (controlMode == cameraControl) {

      //Primero recogemos los valores para el movimiento
      if (joystickA_X < 462 || joystickA_X > 562) {
        if (joystick_X < 462) {
          //Giramos hacia la derecha
          data.valorMotorA = ((joystickA_Y - 562) * 2.216) / 4;
          data.valorMotorB = -((joystickB_Y - 462) * 2.216) / 4;
        }

        if (joystickX > 562) {
        //Giramos a la izquierda
          data.valorMotorA = -((joystickA_Y - 562) * 2.216) / 4;
          data.valorMotorB = ((joystickB_Y - 462) * 2.216) / 4;
        }
      } else {
        if (joystickY < 462) {
          data.valorMotorA = -((462 - joystickA_Y) * 2.216) / 4;
          data.valorMotorB = -((462 - joystickA_Y) * 2.216) / 4;
        } else if (joystickY > 562) {
          data.valorMotorA = ((joystickY - 562) * 2.216) / 4;
          data.valorMotorB = ((joystickY - 562) * 2.216) / 4;
        } else if (joystickY > 462 && joystickY < 562) {
          //Punto parado
          data.valorMotorA = 0.0;
          data.valorMotorB = 0.0;
        }
      }
    }





    Serial.print("Joystick X: ");
    Serial.println(joystickX);
    Serial.print("Joystick Y: ");
    Serial.println(joystickY);


    radio.write(&data, sizeof(data));
    delay(50);
  }
