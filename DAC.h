/**
 * Customized MCP 4922 Library using SPI DAC
 * 
 * Based on:
 * MCP4921/MCP4922 12 bit DAC Library
 * by MichD
 * 
 * Author: Pavel Husa
 */

#include <Arduino.h>

class DAC {
    public:
    DAC(uint8_t, uint8_t);
    void init();

    //Main write function
    void writeData(unsigned int);
    private:
    uint8_t dac_csPin;
    uint8_t dac_latchPin;  
};
