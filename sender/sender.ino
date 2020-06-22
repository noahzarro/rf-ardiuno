/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SEND_TIME 7000

//RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

//seen message

unsigned long int last_seen = millis ();
unsigned long int last_sent = millis ();
unsigned long int last_debug_out = millis(); 

RF24 radio(7, 8); // CE, CSN


void setup ()
{
  Serial.begin (9600);
  radio.begin ();
  radio.openWritingPipe (address);
  radio.setPALevel (RF24_PA_MIN);
  radio.stopListening ();
  pinMode (2, INPUT);


}

void loop ()
{
  if (digitalRead (2) == true)
    {
      // set last_seen to current time
      last_seen = millis ();
    }

  if (millis () < last_seen + SEND_TIME)
    {
      // it has been not more than SEND_TIME since last_seen
      if (millis () > last_sent + 100)
      {
           const char seen_message[] = "x";

        // we haven't sent anything for at least 100ms
        Serial.println("y");
        radio.write (&seen_message, 1);
        last_sent = millis ();
      }
    }

   if(millis() > last_debug_out + 2000){
    Serial.println(sizeof(last_debug_out));
    Serial.println(millis());
    last_debug_out = millis();
    }

}
