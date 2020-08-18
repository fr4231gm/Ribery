#include "RF24.h" 
RF24 myRadio (7, 8); // in Mega can use> (48, 49); 
byte addresses[][6] = {"0"}; 

struct package
{
  float valorAceleracionDelante  = 0.0;
  float valorAceleracionDetras = 0.0;
  int  direccion = 0;
};
typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(100);
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  //motor 1- izquierda
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  //motor 2- derecha
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  //Enables
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  Serial.print("Sistema inicializado");
  
}

void loop()  
{
  if (myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    
    Serial.print("Direccion");
    Serial.print(data.direccion);  
     
    
         
    if(data.direccion == 2){
      digitalWrite(3, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(9, LOW);
    }else if(data.direccion == 4){
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(9, HIGH);
    }else if(data.direccion == 1){
      if(data.valorAceleracionDelante > 30){
        analogWrite(3, data.valorAceleracionDelante-30);
        digitalWrite(5, LOW);
        analogWrite(6, data.valorAceleracionDelante);
        digitalWrite(9, LOW);
      }else if(data.valorAceleracionDetras > 0){
        digitalWrite(3, LOW);
        analogWrite(5, data.valorAceleracionDetras);
        digitalWrite(6, LOW);
        analogWrite(9, data.valorAceleracionDetras);
      }else{
        digitalWrite(3, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(9, LOW);
      }
    }
    
   delay(50);
  }
}
