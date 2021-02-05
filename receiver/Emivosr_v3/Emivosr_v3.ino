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
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

//Valores para los joysticks y declaración de variables

int acelerador = A0;
int girador = A1;
int valorAcelerador = 0;
int valorGirador = 0;



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
  radio.begin();
  delay(1000);
  Serial.println("Inicializando sistema de transmisión");
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.println("Comunication address: 00001");
  delay(400);
  Serial.println("Power Leveol: " + RF24_PA_MIN);
  delay(400);
  Serial.println("Bienvendio");
  delay(200);
  Serial.println("Sistema inicializado");
  
}
void loop() {


  valorAcelerador = analogRead(acelerador);
  valorGirador = analogRead(girador);


  if(valorGirador <462 || valorGirador > 562){
    if(valorGirador <462){
    data.direccion = 4;
    data.valorAceleracionDelante = 0.0;
    data.valorAceleracionDetras = 0.0;
  }
  
  if(valorGirador > 562){
    data.direccion = 2;
    data.valorAceleracionDelante = 0.0;
    data.valorAceleracionDetras = 0.0;
  }
  }else{
    data.direccion = 1;
    Serial.print("Valor acelerador");
    Serial.println(valorAcelerador);
    if(valorAcelerador < 462){
    //Acelerador en modo marcha atrás
    data.valorAceleracionDelante = 0.0;
    data.valorAceleracionDetras = ((462 - valorAcelerador) * 2.216)/4;
  }else if(valorAcelerador > 562){
    //Acelerador en modo marcha delante
    data.valorAceleracionDetras = 0.0;
    data.valorAceleracionDelante = ((valorAcelerador - 562) * 2.216)/4;
  }else if(valorAcelerador > 462 && valorAcelerador <562){
    //Punto parado
    data.valorAceleracionDelante = 0.0;
    data.valorAceleracionDetras = 0.0;
  }
  }

  
  radio.write(&data, sizeof(data));
  delay(50);
}
