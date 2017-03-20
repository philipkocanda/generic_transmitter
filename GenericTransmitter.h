/*
 * GenericTransmitter library by Philip Kocanda
 *
 * License: GPLv3. See license.txt
 */

#ifndef GenericTransmitter_h
#define GenericTransmitter_h

#include <Arduino.h>

class GenericTransmitter {
  public:
    /**
    * Constructor.
    *
    * @param id       Device ID (0-15999)
    * @param pin      Output pin on which the transmitter is connected
    * @param repeats  2-8 (default: 4)
    */
    GenericTransmitter(unsigned long id, unsigned short pin, unsigned short repeats = 4);

    /**
    * @param type     Device type (0-15)
    * @param value    Value to send (unsigned)
    * @param positive
    */
    void transmit(unsigned long type, unsigned long value, boolean positive);

    /**
    * @param type     Device type (0-15)
    * @param value    Value to send (signed)
    */
    void transmit(unsigned long type, signed long value);

  protected:
    unsigned long _id;        // Device ID
    unsigned short _pin;      // Transmitter output pin
    unsigned short _repeats;  // Number over repetitions of one telegram

    /**
    * @param type     Device type (0-15)
    * @param value    Value to send (unsigned)
    * @param positive
    */
    void _transmit(unsigned long type, unsigned long value, boolean positive);

    /**
     * Transmits stop pulse.
     */
    void _sendStopPulse();

    /**
     * Transmits a single bit.
     *
     * @param b  True, to send '1', false to send '0'.
     */
    void _sendBit(boolean b);

    /**
     * Convert 0 in 01 and 1 in 10 (Manchester conversion)
     *
     * @param b  True, to send '1', false to send '0'.
     */
    void _sendPair(boolean b);

    /**
     * Integer to Bytes
     */
    void _itob(int* bytes, unsigned long integer, int length);

    /**
     * Power of 2
     */
    unsigned long _power2(int power);
};
#endif
