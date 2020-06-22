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

// time the relais should be on after the last "x" received
#define RUN_TIME 240000

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// time at which the last "x" was received
unsigned long int last_received = millis();

// indicates if relais is currently on
bool relais_on = false;

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop()
{
  // if there is a message, check content
  if (radio.available())
  {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    // if the message is "x" print it and reset last_received to current time
    if (text == "x")
    {
      Serial.println(text);
      last_received = millis();
    }
  }

  // if it is not later than RUN_TIME after last_received the relais should be on
  if (millis() < last_received + RUN_TIME)
  {
    // this just done to not to spam the arduino with constant digitalWrites. It would also work without the additional if
    if (relais_on == false)
    {
      // if relais was off before, switch it on
      digitalWrite(2, HIGH);
    }

    relais_on = true;
  }
  else
  {
    // this just done to not to spam the arduino with constant digitalWrites. It would also work without the additional if
    if (relais_on == true)
    {
      // if relais was on before, switch it off
      digitalWrite(2, LOW);
    }

    relais_on = false;
  }
}
