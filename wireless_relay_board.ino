#include "src/BlinkableLED/BlinkableLED.hpp"
#include "src/Relay/Relay.hpp"
#include "src/Radio/Radio.hpp"
#include "constants/PinConstants.hpp"

// Radio
Radio radio;
unsigned long timeOfPreviousTxInMilliseconds;
const int intervalBetweenTxInMilliseconds{1000};

// LEDs
BlinkableLED rxLED{PinConstants::rxLEDPin};
BlinkableLED txLED{PinConstants::txLEDPin};

// Relays
Relay firstRelay{PinConstants::firstRelayPin};
Relay secondRelay{PinConstants::secondRelayPin};

void setup(){
  radio.init();
}

void loop(){
  if (isTxDue()){
    txRelayStates();
  }
  
  radio.receiveByte(&receiveByteCallback);

  rxLED.updateState();
  txLED.updateState();
}

bool isTxDue(){
  return millis() - timeOfPreviousTxInMilliseconds >= intervalBetweenTxInMilliseconds;
}

void txRelayStates(){
  radio.sendByte(serializeRelayStates());
  txLED.blink();
  timeOfPreviousTxInMilliseconds = millis();
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
  
  // Transmit a signal as soon as possible after receiving. This gives a response
  // almost immediately to the controller device.
  makeTxDue();
}

void makeTxDue(){
  timeOfPreviousTxInMilliseconds = 0;
}