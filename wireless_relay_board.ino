#include "src/BlinkableLED/BlinkableLED.hpp"
#include "src/Relay/Relay.hpp"
#include "src/Radio/Radio.hpp"

// Radio
Radio radio;

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

void setup(){
  radio.init();
}

void loop(){
  if (isTxDue()){
    radio.sendByte(serializeRelayStates());
    txLED.blink();
    timeOfPreviousTxInMilliseconds = millis();
  }
  
  radio.receiveByte(&receiveByteCallback);

  rxLED.updateState();
  txLED.updateState();
}

bool isTxDue(){
  return millis() - timeOfPreviousTxInMilliseconds >= intervalBetweenTxInMilliseconds;
}

uint8_t serializeRelayStates(){
  // Bit 0 represents the state of the second relay, bit 1 represents the state of the first relay.
  return (firstRelay.isTurnedOn() << 1) | secondRelay.isTurnedOn();
}

void receiveByteCallback(uint8_t byte){
  bool shouldFirstRelayBeTurnedOn{byte & (1 << 1)};
  bool shouldSecondRelayBeTurnedOn{byte & 1};

  shouldFirstRelayBeTurnedOn ? firstRelay.turnOn() : firstRelay.turnOff();
  shouldSecondRelayBeTurnedOn ? secondRelay.turnOn() : secondRelay.turnOff();

  rxLED.blink();
}