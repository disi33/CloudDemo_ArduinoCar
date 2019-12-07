# Table of contents

* [Repository contents](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#repository-contents)

* [Hardware and accessories](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#hardware-and-accessories)
  - [Hardware](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#hardware)
  - [Accessories](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#accessories)
  
* [Modules](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#modules)
  * [GPS Module](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#gps-module)
  * [ESP8266 (WiFi module)](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#esp8266-wifi-module)
    * [Notes on ESP8266](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#notes-on-esp8266)
    * [Additional notes](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#additional-notes)
  * [Wireless XBOX 360 adapter](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#wireless-xbox-360-adapter)
  
* [Software](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#software)
  - [Libraries](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#libraries)
  - [Enabling and disabling modules](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#enabling-and-disabling-modules)
  - [Notes on the implementation](https://github.com/disi33/CloudDemo_ArduinoCar/blob/master/README.md#notes-on-the-implementation)

# Repository contents

This repository contains:
- The source code of the program run on the car
- Schematics and reference pictures of the power-regulated WiFi module and the final build of the car
  * The schematics are made with [fritzing](http://fritzing.org/home/). You can use fritzing to open the .fzz file and edit the schematics or use it to create a proper PCB.
- A list of hardware and accessories used to finish this project

# Hardware and accessories

## Hardware
- The base [RC car kit](https://www.amazon.com/VKmaker-Avoidance-tracking-Ultrasonic-tutorial/dp/B01CXVA6IO/ref=sr_1_9?crid=3F1P4S1285E54&keywords=arduino+rc+car+kit&qid=1566278970&s=gateway&sprefix=arduino+rc%2Caps%2C212&sr=8-9).
- An [Arduino USB host shield](https://www.amazon.com/gp/product/B006J4G000/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) for USB capabilities to enable XBOX controllers.
- An [Arduino Sensor shield](https://www.amazon.com/KNACRO-Sensor-Expansion-Arduino-Genuino/dp/B01N2OLLH0/ref=sr_1_3?keywords=arduino+sensor+shield&qid=1566279327&s=electronics&sr=1-3) for better access to pins and easier wiring.
- An [XBOX 360 wireless controller](https://www.amazon.com/gp/product/B073WJCQGT/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1) and [receiver](https://www.amazon.com/gp/product/B00TGL39TI/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1).
- A [GPS module](https://www.amazon.com/gp/product/B01AW5QYES/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1).
- An [ESP8266 ESP-01 WiFi module](https://www.amazon.com/MakerFocus-Wireless-Transceiver-DC3-0-3-6V-Compatible/dp/B01EA3UJJ4/ref=sr_1_6?crid=255TF5ZGUCMDT&keywords=esp8266&qid=1566279614&s=electronics&sprefix=esp%2Celectronics%2C216&sr=1-6)
- A [3.3V Step Down Power Supply Voltage Regulator](https://www.amazon.com/gp/product/B01N1I1LXH/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) module.
- A roughly [3x7cm prototype board](https://www.amazon.com/uxcell-Universal-Printed-Circuit-Soldering/dp/B07FK47K22/ref=sr_1_2?keywords=prototype+board+24x10&qid=1566279837&s=electronics&sr=1-2-catcorr) as a base for the power-regulated WiFi module.
- A [400 pin breadboard](https://www.amazon.com/gp/product/B077DN2PS1/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1) to fit the extra components neatly above the battry pack in the back of the car.
- A reasonable assortments of electronic parts (resistors: 1k, 2k, 10k; capacitors: 0.22uF, 470uF; jumper cables; [male and female pin header connector rows](https://www.amazon.com/Pieces-Female-Connector-Straight-Arduino/dp/B07VNXL5BD/ref=sr_1_1_sspa?keywords=pin+male+connectors&qid=1566281021&s=industrial&sr=1-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFFVUU1RjEzRVBUU1MmZW5jcnlwdGVkSWQ9QTA0NDM4MTkxT1VEQVhXQVg2VkMwJmVuY3J5cHRlZEFkSWQ9QTA5MjY0OTgzTlY3NUhOTkMyVjBQJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==))

## Accessories

- soldering kit
- AA batteries for the car and the XBOX 360 controller
- [USB Serial module for the ESP8266](https://www.amazon.com/gp/product/B07KF119YB/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
- tape for fixing the breadboard and the wireless controller adapter to the car
- optional: rubber bands (the tires in some car kits do not create enough friction on most surfaces, you can put rubber bands around them to increase traction)

# Modules

## GPS Module

The GPS module is connected as follows:

| GPS | -   | Arduino     |
|-----|-----|-------------|
| VCC | <-> | +5V         |
| GND | <-> | GND         |
| TxD | <-> | PIN 18 (A4) |
| RxD | <-> | PIN 19 (A5) |

## ESP8266 (WiFi module)

**ATTENTION:** The ESP8266 operates on 3.3V, while the Arduino operates on 5V! Do not connect the ESP8266 to 5V, use a step down regulator to convert the Voltage. The ESP8266 may not function correctly or even break/brick if operated under 5V. For the same reasons, use a 1k and a 2k resistor to step down the signal coming from the arduino on the ESP8266's RxD line!

The ESP8266 is generally connected as follows:

| ESP8266 | -   | Arduino                                    |
|---------|-----|--------------------------------------------|
| VCC     | <-> | +3.3V (generated from step down regulator) |
| GND     | <-> | GND                                        |
| TxD     | <-> | PIN 4                                      |
| RxD     | <-> | PIN 3 (through step down resistors)        |
| CH_PD   | <-> | +3.3V (through 10k pull-up resistor)       |

### Notes on ESP8266:

When idle, the ESP8266 draws about 30-50 mA, but during peak load draws of about 300mA are not unseen. I recommend to use stabilizer capacitors of 470uF near the step down regulator and 0.22uF near the ESP8266 to help with sudden spikes. The capacitors should be as near as possible to their respective counterpart parts, since too much resistance on the cables running up to them can negate their intended functionality.

So all-in-all the ESP8266 requires quite a bit of extra work here:
- step down power source voltage from 5V to 3.3V
- add additional step down resistors for incoming signals from Arduino
- a pull up resistor for CH_PD
- stabilizing capacitors for smoother power supply during peak load times

The breadboard can be very restrictive in space and in how to place these components, so I recommend creating this circuit as a separate module on a prototype board. When doing so, please keep these things in mind:
- You can solder a piece of a male connector row to the bottom of the connector board, that way you can put the module into the breadboard vertically.
- Ensure the capacitors are placed close to the step down regulator and the ESP8266 respectively.
- You can use 2 4-pieces of female connector rows as a base for the ESP8266 to sit in. That way you can easily remove it for programming purposes or replace it when broken.

### Additional notes:

Most ESP8266 come pre-programmed to a baud rate of 115200. Arduinos regularly struggle to communicate at such a baud rate over Serial buses and it is recommended to user a lower baud rate. Use a USB interface to manually set the baud rate of the ESP8266 to 9600. (All source code distributed in this repo assumes a baud rate of 9600.)

A power supply of 6 AA-batteries should mostly be sufficient to operate the ESP8266 in addition to all other components on the car. That being said, I have experienced situation where the ESP8266 was suddenly becoming unresponsive. I suspect this is due to the power supply not being able to supply high enough current during peak workload, so I recommend not spamming the module with HTTP requests and limiting the use to 1 request every few seconds to minimize the need for resets.

## Wireless XBOX 360 adapter

Use the USB shield to connect the USB adapter to the Arduino. You can run the cable underneath the base plate of the car and use tape to fix the cable and the receiver to the bottom of the plate.

# Software

Use the [Arduino IDE](https://www.arduino.cc/en/Main/Software) to upload the program onto the Arduino and to read the output on the Serial connection via the IDE's Serial Monitor.

## Libraries

This project is using:
- the [USB Host Shield Library 2.0](https://github.com/felis/USB_Host_Shield_2.0) to connect to the XBOX Controller via the wireless adapter.
- the [ESP8266_Simple library](https://github.com/sleemanj/ESP8266_Simple) to operate the ESP8266 module.

## Enabling and disabling modules

The program consists of 3 basic modules that can be enabled and disabled before uploading the program to the Arduino:
- **Controller:** for remote controlling the car using an XBOX 360 controller
- **GPS:** for reading the car's GPS location
- **WiFi:** for spinning up a HTTP server on the car to interact with it over WiFi

You can enable and disable these modules on top of the program file. When enabling the WiFi module, you must also specify the SSID and password of the WiFi network to connect to.

## Notes on the implementation

- Both the USB Host Shield library and the ESP8266_Simple library are using the [SoftwareSerial library](https://www.arduino.cc/en/Reference/SoftwareSerial) to communicate with their respective modules. Unfortunately, while SoftwareSerial allows for specifying several Serial connections on different pins, as of now this library only allows for **only one Serial port to be operated at a time**. Especially the ESP8266_Simple library seems to struggle to maintain its internal state when a different SoftwareSerial port is being operated. Enabling this functionality would require a complete overhaul of the used libraries. To work around this, for now the GPS data is only read from the GPS module once before the ESP8266_Simple Serial connection is established.
- At the time of writing this, some of the used libraries are incompatible with the latest version of the **Arduino AVR Boards** board libraries used by the Arduino IDE. When running into issues while compiling or uploading the program, try downgrading the library version to version **1.6.20** in the IDE's board manager.
- The controller module allows for remote controlling the cars movement using the D-Pad. The current implementation is very basic and might occasionally drop an input, but should be sufficient for demo purposes.
- The program is writing quite some information to the default Serial connection. You can use the Arduino IDE's Serial Monitor to debug the program if the car shows unexpected behavior. Note that the demo software used to display the car's IP address after establishing WiFi connection on the serial port, but due to some incompatibilities between the latest ESP8266 firmware and the latest Arduino libraries, we cannot easily do that right now. I recommend setting up the demo using a phone hotspot and reading the IP address from your phone as a fast way to get a connection and knowing the car's IP address.
