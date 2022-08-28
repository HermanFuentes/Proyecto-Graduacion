#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 8
#define CSN_PIN 9
 
//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'c','a','n','a','l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datos a enviar
float datos[6];

void setup()
{
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
 
//Abrimos un canal de escritura
 radio.openWritingPipe(direccion);
   radio.openReadingPipe(1, direccion);
  radio.setPALevel(RF24_PA_MAX);
}
 
void loop()
{ 
 //cargamos los datos en la variable datos[]
 datos[0]=analogRead(0);
 datos[1]=analogRead(1);
 datos[3]=0;
 datos[4]=0;
 datos[5]=0;
 //enviamos los datos
 bool ok = radio.write(datos, sizeof(datos));
  //reportamos por el puerto serial los datos enviados 
  if(ok)
  {
     Serial.print("----------"); 
    /* Serial.print(datos[0]); 
     Serial.print(" , "); 
     Serial.print(datos[1]); 
     Serial.print(" , "); 
     Serial.println(datos[2]); 
     */
       
  }
  else
  {
     Serial.println("no se ha podido enviar");
 
  }

  //test

   radio.startListening();
   uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if ( radio.available() )
 {    
     //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
     
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Dato4= " );
     Serial.print(datos[4]);
     Serial.print(" V, ");
     Serial.print("Dato5= " );
     Serial.print(datos[5]);
     Serial.print(" ms, ");
     Serial.print("Dato6= " );
     Serial.println(datos[5]);
 }
 else
 {
     Serial.println("------------");
 }
     radio.stopListening();
delay(5);
}
