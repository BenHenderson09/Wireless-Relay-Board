#include <LoRa.h>
#include "src/BlinkableLED/BlinkableLED.hpp"
#include "src/Relay/Relay.hpp"

// Radio
const long radioFrequency{433E6};

// LEDs
const int txLEDPin{3};
const int rxLEDPin{4};
unsigned long timeOfPreviousTxInMilliseconds;
const int intervalBetweenTxInMilliseconds{1000};

BlinkableLED rxLED{rxLEDPin};
BlinkableLED txLED{txLEDPin};

// Relays
const int firstRelayPin{5};
const int secondRelayPin{6};

Relay firstRelay{firstRelayPin};
Relay secondRelay{secondRelayPin};

void setup() {
  setupLoRa();
}

void loop() {
  if (!firstRelay.isTurnedOn()){
    firstRelay.turnOn();
  }

  if (!secondRelay.isTurnedOn()){
    secondRelay.turnOn();
  }
  
  if (isTxDue()){
    sendPacket();
  }
  
  if (LoRa.parsePacket()){
    rxLED.blink();
  }

  rxLED.updateState();
  txLED.updateState();
}

void setupLoRa(){
  if (!LoRa.begin(radioFrequency)) {
    while (1);
  }

  LoRa.setTxPower(15);
}

bool isTxDue(){
  return millis() - timeOfPreviousTxInMilliseconds >= intervalBetweenTxInMilliseconds;
}

void sendPacket(){
  txLED.blink();
  timeOfPreviousTxInMilliseconds = millis();
  
  // Bit 0 represents the state of the second relay, bit 1 represents the state of the first relay.
  uint8_t message{(firstRelay.isTurnedOn() << 1) | secondRelay.isTurnedOn()};

  LoRa.beginPacket();
  LoRa.write(message);
  LoRa.endPacket(true);
} 
