# Generic Library (Arduino > Pimatic with Homeduino)

Turns any Arduino with a 433 MHz transmitter into a wireless sensor probe / data logger for Pimatic.
Transmits temperature, humidity, or any other numeric reading to your Pimatic home automation system.

# Prerequisites

- Arduino with 433 MHz transmitter
- Pimatic with the Homeduino plugin and a 433 MHz receiver hooked up

# Demo

- Wire up the 433 mhz transmitter to the correct pin (see Demo.ino)
- Flash Demo.ino to your Arduino 
- Watch the sensor readings appear in the Pimatic debug logs

# Piping data to a Pimatic (with Homeduino) Device

- You can configure a Generic RF Device with the same Device ID / Device Type that you configured on the Arduino.
- The Homeduino plugin will then update that device with the received data.
- It's possible to have multiple attributes per device.


I need to update this guide but I haven't had the time yet.. Sorry!
