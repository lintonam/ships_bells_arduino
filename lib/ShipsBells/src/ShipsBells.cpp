#include "ShipsBells.h"

ShipsBells::ShipsBells(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void ShipsBells::singleStrike()
{
  digitalWrite(_pin,HIGH);
  delay(200);
  digitalWrite(_pin,LOW);
  delay(350);
}

void ShipsBells::doubleStrike()
{
  digitalWrite(_pin,HIGH);
  delay(200);
  digitalWrite(_pin,LOW);
  delay(350);
  digitalWrite(_pin,HIGH);
  delay(200);
  digitalWrite(_pin,LOW);
  delay(500);
}
