#include <LoRa.h>
#include "Radio.hpp"
#include "../../constants/RadioConstants.hpp"

void Radio::init(){
    if (!LoRa.begin(RadioConstants::radioFrequency)) {
        while (1);
    }
}

void Radio::sendByte(uint8_t byte){
    LoRa.beginPacket();
    LoRa.write(byte);
    LoRa.endPacket();
}

void Radio::receiveByte(void(*receiveByteCallback)(uint8_t)){
    if (LoRa.parsePacket()){
        (*receiveByteCallback)(LoRa.read());
    }
}