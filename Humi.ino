#include <dht.h>
dht DHT;
char A;
char B = 0; // Assumes humidifer is off on boot.


void setup()
{
  Serial.begin(9600);
  pinMode(1, OUTPUT);
}


void loop()
{
  H();  //  Checks humidity data and returns 2 if over 75
  A = H();  //  Preparess H data for decision.
  if (A + B == 1) //  First run should ignore this
  {
    onOff();  //  Low humdity. Turning machine off.
    Serial.println ("A + B = 1. Turning machine off");
    B = 0;  //  Declaring machine is now off.
  }
  if (A + B == 2)
  {
    onOff();  //  Machine is off and humidity is high. Machine turning on.
    Serial.println("A + B = 2. Turning machine on");
    B = 1;  //  Declaring that machine is now on.
  }
  Serial.println(DHT.humidity);
  delay(2000);
}

byte H()  //  Function to detirmine if humdity is high.
{
  DHT.read11(A0);
  if (DHT.humidity >= 75)
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

void onOff()  //  Pulses current to the capacative spring to flip it.
{
  digitalWrite(1, HIGH);
  digitalWrite(1, LOW);
}
