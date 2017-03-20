// Transmitter
#include <GenericTransmitter.h>
#define TRANSMITTER_PIN 5 // 433 mhz transmitter data pin
#define TRANSMITTER_REPEATS 4
#define DEVICE_ID 10
#define TEMPERATURE_TYPE 1
#define HUMIDITY_TYPE 2

// Temperature Sensor
#include "DHT.h"
#define DHT_TYPE DHT22
#define DHT_PIN 6

#define DEBUG false

GenericTransmitter transmitter(DEVICE_ID, TRANSMITTER_PIN, TRANSMITTER_REPEATS);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  if (DEBUG) { Serial.begin(9600); }
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    if (DEBUG) {
      Serial.println("Failed to read from DHT sensor!");
    }
    return;
  }

  int int_t = int (t * 100);
  int int_h = int (h * 100);

  transmitter.transmit(TEMPERATURE_TYPE, int_t);
  transmitter.transmit(HUMIDITY_TYPE, int_h);

  delay(60000 * 5); // every 5 minutes
}
