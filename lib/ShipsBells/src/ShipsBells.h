/*
  ShipsBells.h - Library for striking Ships Bells.
  Created by Aaron Linton, October 28, 2016.
  Released into the public domain.
*/
#ifndef ShipsBells_h
#define ShipsBells_h

#include "Arduino.h"

class ShipsBells
{
public:
  ShipsBells(int pin);
  void singleStrike();
  void doubleStrike();
private:
  int _pin;
};

#endif
