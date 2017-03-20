// Transmitter
#include <GenericTransmitter.h>
#define TRANSMITTER_PIN 5 // 433 mhz transmitter data pin
#define TRANSMITTER_REPEATS 4
#define DEVICE_ID 10
#define DEVICE_TYPE 100
GenericTransmitter transmitter(DEVICE_ID, TRANSMITTER_PIN, TRANSMITTER_REPEATS);

int transmit_value = 0;

void setup() {
}

// Transmit an increasing number every five seconds.
// This is the most basic transmitter possible.
void loop() {
  transmit_value++;

  transmitter.transmit(DEVICE_TYPE, transmit_value);

  delay(5000);
}
