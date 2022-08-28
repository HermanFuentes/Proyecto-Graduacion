#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 #include <Servo.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 8
#define CSN_PIN 9
 
//Variable con la dirección del canal que se va a leer
byte direccion[5] ={'c','a','n','a','l'}; 

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);
Servo myServo;
Servo myServo2;
//vector para los datos recibidos
float datos[6];
int angleValue=0;int angleValue2=0;
void setup()
{  myServo.attach(2);
myServo2.attach(3);

 //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  
  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);
   radio.openWritingPipe(direccion);
  radio.setPALevel(RF24_PA_MAX);

    //empezamos a escuchar por el canal

 
}
 
void loop() {
    radio.startListening();
 uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if ( radio.available() )
 {    
     //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
     
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Dato0= " );
     Serial.print(datos[0]);
     angleValue = map(datos[0], 0, 1023, 0, 180);  
     myServo.write(angleValue);
     Serial.print(" V, ");
     Serial.print("Dato1= " );
     Serial.print(datos[1]);
     angleValue2 = map(datos[1], 0, 1023, 0, 180);  
     myServo2.write(angleValue2);
     Serial.print(" ms, ");
     Serial.print("Dato2= " );
     Serial.println(datos[2]);
       Serial.println(angleValue);
 }
 else
 {
     Serial.println("No hay datos de radio disponibles");
 }
    radio.stopListening();

 //test
 datos[3]=analogRead(A0);
 datos[4]=analogRead(A1);
 datos[5]=analogRead(A2);
 //enviamos los datos
 bool ok = radio.write(datos, sizeof(datos));
  //reportamos por el puerto serial los datos enviados 
  if(ok)
  {
     Serial.print("Datos enviados: "); 
     //Serial.print(datos[3]); 
     //Serial.print(" , "); 
    // Serial.print(datos[4]); 
    // Serial.print(" , "); 
   //  Serial.println(datos[5]); 
  }
  else
  {
     Serial.println("no se ha podido enviar");
  }
 delay(5);
}
