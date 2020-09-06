#include <Arduino.h>
#include "Relay.hpp"

Relay::Relay(int pin) : pin{pin}{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);
}

bool Relay::isTurnedOn(){
    return state == ON_STATE;
}

void Relay::turnOff(){
    // Don't do unnecessary writes if already turned off
    if (state == ON_STATE){
        state = OFF_STATE;
        digitalWrite(pin, state);
    }
}

void Relay::turnOn(){
    // Don't do unnecessary writes if already turned on
    if (state == OFF_STATE){
        state = ON_STATE;
        digitalWrite(pin, state);
    }
}
