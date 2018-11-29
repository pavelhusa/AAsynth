/**
 * Customized MCP 4922 Library using SPI DAC
 * based on:
 * MCP4921/MCP4922 12 bit DAC Library
 * By MichD
 * Author: Pavel Husa
 */
#include <SPI.h>
#include "DAC.h"

DAC::DAC(uint8_t cs_pin, uint8_t latch_pin) {
    dac_csPin = cs_pin;
    dac_latchPin = latch_pin;
    init();
}

void DAC::init() {
    pinMode(dac_csPin, OUTPUT);
    pinMode(dac_latchPin, OUTPUT);
    digitalWrite(dac_csPin, HIGH);
    SPI.begin();
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    //SPI.setClockDivider(SPI_CLOCK_DIV2);
}

void DAC::writeData(uint16_t data) {
    //digitalWrite(_csPin, 0);
    PORTB &= ~0x2; //Hardwired PIN 9
    SPI.transfer(B0111 << 4 | (data & 0xF00) >> 8);
    SPI.transfer(data & 0xFF);  
    //digitalWrite(_csPin, 1);
    PORTB |= 0x2; //Hardwired PIN 9
    //digitalWrite(_latchPin, 0);
    //digitalWrite(_latchPin, 1);
    PORTB &= ~0x4; //Hardwired PIN 10
    asm volatile("nop");
    PORTB |= 0x4; //Hardwired PIN 10
}
