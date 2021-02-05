/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

struct package
{
  float valorAceleracionDelante  = 0.0;
  float valorAceleracionDetras = 0.0;
  int  direccion = 0;
};
typedef struct package Package;
Package data;


void setup() {

    Serial.begin(9600);
    Serial.println("Inicializando pines de motores");
    delay(400);
  //Motor izquierda
  //IN1
   pinMode(6, OUTPUT);
   //IN2
   pinMode(5, OUTPUT);
   //EN
   pinMode(2, OUTPUT);
   //Motor derecha
   //IN3
   pinMode(3, OUTPUT);
   //IN4
   pinMode(7, OUTPUT);
  //ENABLE
   pinMode(8,OUTPUT);
 
   digitalWrite(8, HIGH);
   digitalWrite(2, HIGH);
  
  Serial.println("Inicializando radio");
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Serial.println("Comunication address: 00001");
  delay(400);
  Serial.println("Power Leveol: " + RF24_PA_MIN);
  delay(400);
  Serial.println("Bienvendio");
  delay(200);
  Serial.println("Sistema inicializado");
  
}
void loop() {

   if (radio.available()) 
  {
    while (radio.available())
    {
      radio.read( &data, sizeof(data) );
    }
    
    Serial.print("Direccion");
    Serial.print(data.direccion);  
     
    
         
    if(data.direccion == 2){
      digitalWrite(3, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(11, LOW);
    }else if(data.direccion == 4){
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(11, HIGH);
    }else if(data.direccion == 1){
      if(data.valorAceleracionDelante > 30){
        analogWrite(3, data.valorAceleracionDelante-30);
        digitalWrite(5, LOW);
        analogWrite(6, data.valorAceleracionDelante);
        digitalWrite(11, LOW);
      }else if(data.valorAceleracionDetras > 0){
        digitalWrite(3, LOW);
        analogWrite(5, data.valorAceleracionDetras);
        digitalWrite(6, LOW);
        analogWrite(11, data.valorAceleracionDetras);
      }else{
        digitalWrite(3, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(11, LOW);
      }
    }
    
   delay(50);
  }
}
