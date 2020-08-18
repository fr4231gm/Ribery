#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 myRadio (7, 8); // in Mega can use> (48, 49); 
byte addresses[][6] = {"0"}; 
int acelerador = A0;
int girador = A1;
int camaraX = A2;
int camaraY = A3;
int valorGirador = 0;
int valorAcelerador = 0;

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

struct package
{
  float camaraEnX = 0.0;
  float camaraEnY = 0.0;
  float valorAceleracionDelante  = 0.0;
  float valorAceleracionDetras = 0.0;
  int  direccion = 0;
};
typedef struct package Package;
Package data;

void setup()
{
  Serial.begin(9600);
  delay(100);
  myRadio.begin();  
  myRadio.openWritingPipe(pipe);


}

void loop()
{

  
  camaraEnX = analogRead(camaraX);
  camaraEnY = analogRead(camaraY);
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
  Serial.print("Derecha");
  Serial.println(digitalRead(2));
  Serial.print("Izquierda");
  Serial.println(digitalRead(9));
  Serial.print("Aceleracion adelante");
  Serial.println(data.valorAceleracionDelante);
  Serial.print("Aceleracion atras");
  Serial.println(data.valorAceleracionDetras);
  myRadio.write(&data, sizeof(data)); 
  
  
  delay(50);
}
