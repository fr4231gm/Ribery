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

float data[3];

void setup() {
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
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
   int valor;
   if (radio.available())
   {    
      radio.read(data, sizeof data);
      Serial.print(data[0]);
      if(data[0] = 1){
        valor = 1;
      }else if(data[0] = 2){
        valor = 2;
      }else if(data[0] = 3){
        valor = 3;
      }else if(data[0] = 4){
        valor = 4;
      }
   }


    if(valor = 1){
      //Hacia delante
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(3, LOW);
    }else if(valor = 2){
      //Hacia atrás
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(3, HIGH);
    }else if(valor = 3){
      //Gira izquierda
      digitalWrite(11, HIGH);
      digitalWrite(3, LOW);
    }else if(valor = 4){
      //Gira derecha
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
    }
   
   delay(1000);
}
