/*
 * GenericTransmitter library by Philip Kocanda
 * See GenericTransmitter.h for details.
 *
 * License: GPLv3. See license.txt
 */

#include "GenericTransmitter.h"

GenericTransmitter::GenericTransmitter(unsigned long id, unsigned short pin, unsigned short repeats) {
  _id = id;
  _pin = pin;
  _repeats = repeats;

  pinMode(_pin, OUTPUT);
}


void GenericTransmitter::transmit(unsigned long type, unsigned long value, boolean positive) {
  _transmit(type, value, positive);
}

void GenericTransmitter::transmit(unsigned long type, signed long value) {
  if (value > 0) {
    _transmit(type, value, true);
  } else {
    _transmit(type, abs(value), false);
  }
}

void GenericTransmitter::_transmit(unsigned long type, unsigned long value, boolean positive) {
  for (int i = _repeats; i >= 0; i--) {
    int BytesId[14];
    int BytesType[4];
    int BytesData[30];

    _itob(BytesId, _id, 14);
    _itob(BytesType, type, 4);
    _itob(BytesData, value, 30);

    // Send the unique ID of your Arduino node
    for (int j=0; j<14; j++)
    {
      _sendPair(BytesId[j]);
    }

    // Send protocol type
    for (int j = 0; j<4; j++)
    {
      _sendPair(BytesType[j]);
    }

    // Send the flag to mark the value as positive or negative
    _sendPair(positive);

    // Send value
    for (int j = 0; j<30; j++)
    {
      _sendPair(BytesData[j]);
    }

    _sendStopPulse();
  }
}

void GenericTransmitter::_sendStopPulse() {
  digitalWrite(_pin, HIGH);
  delayMicroseconds(506);
  digitalWrite(_pin, LOW);
  delayMicroseconds(8602);
}

// Send one bit
//
// 1 = 310µs high, 1340µs low
// 0 = 310µs high, 310µs low
void GenericTransmitter::_sendBit(boolean b) {
 if (b) {
   digitalWrite(_pin, HIGH);
   delayMicroseconds(506); // 305 orinally, but tweaked.
   digitalWrite(_pin, LOW);
   delayMicroseconds(2024); // 1225 orinally, but tweaked.
 }
 else {
   digitalWrite(_pin, HIGH);
   delayMicroseconds(506); // 305 orinally, but tweaked.
   digitalWrite(_pin, LOW);
   delayMicroseconds(4301); // 305 orinally, but tweaked.
 }
}

// Convert 0 in 01 and 1 in 10 (Manchester conversion)
void GenericTransmitter::_sendPair(boolean b) {
  if (b)
  {
    _sendBit(true);
    _sendBit(false);
  }
  else
  {
  _sendBit(false);
  _sendBit(true);
  }
}

// integer to byte
void GenericTransmitter::_itob(int* bytes, unsigned long integer, int length)
{
 for (int i=0; i<length; i++){
   if ((integer / _power2(length-1-i))==1){
     integer-=_power2(length-1-i);
     bytes[i]=1;
   }
   else bytes[i] = 0;
 }
}

//gives 2 to the (power)
unsigned long GenericTransmitter::_power2(int power){
 unsigned long integer=1;
 for (int i=0; i<power; i++){
   integer*=2;
 }
 return integer;
}
