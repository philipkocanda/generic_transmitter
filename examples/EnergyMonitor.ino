// Transmitter
#include <GenericTransmitter.h>
#define TRANSMITTER_PIN 5 // 433 mhz transmitter data pin
#define TRANSMITTER_REPEATS 4
#define DEVICE_ID 10
#define DEVICE_TYPE 100
GenericTransmitter transmitter(DEVICE_ID, TRANSMITTER_PIN, TRANSMITTER_REPEATS);

// Energy Monitor
#include <EmonLib.h>
#define EMON_ANALOG_PIN 4 // current sensor pin
#define EMON_CALIBRATION 4 // calculate this yourself
EnergyMonitor emon1;

void setup()
{
  emon1.current(EMON_ANALOG_PIN, EMON_CALIBRATION);
}

void loop() {
  int voltage = 230;
  int current = emon1.calcIrms(1480);
  int power = current * voltage; // Watts

  transmitter.transmit(DEVICE_TYPE, power);
  delay(10000);
}
