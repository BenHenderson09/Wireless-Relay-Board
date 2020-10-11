# Wireless Relay Board
A device which exposes mains sockets for appliances, and controls their on/off state via relays.
The relays act in accordance to instructions wirelessly received from a controller device.

![](https://github.com/BenHenderson09/Wireless-Relay-Board/blob/master/board.jpg)

## Details
- Can alter the states of two 240vac mains sockets.
- A LoRa SX1278 acts as a transceiver for both broadcasting the relay states and receiving commands
from the controller.
- An Arduino Uno works with the LoRa module to manage communications with the controller. The Arduino
will also control a dual relay module which is wired into the sockets.
- Makes use of RC snubbers
- AC/DC adapter circuit converts mains to 12VDC for the Arduino