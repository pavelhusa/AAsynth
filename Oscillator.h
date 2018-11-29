/**
 *  Based od Arduino for Musicians
 *  Brent Edstrom, 2013
 * 
 *  Author: Pavel Husa
 *  
 *  Desc: Oscillator class returns value 0-4095. 
 */

#ifndef SYNTH_OSCILLATOR
#define SYNTH_OSCILLATOR

#include <Arduino.h>
#include "Tables.h"

class Oscillator {
  private:
  volatile uint32_t osc_accumulator;
  volatile uint32_t osc_increment;
  
  public:
  Oscillator();
  unsigned char osc_detune;
  unsigned char osc_note;  
  
  void setNote(unsigned char note);
  void detune(unsigned char d);
  void reset();
  /*
   * Time critical - MUST BE INLINE!!!
   * This method is overriden in oscilator-shapes subclass.
   */
  inline virtual uint32_t getSample() {
    osc_accumulator += osc_increment;
    return osc_accumulator;
  }
};

#endif
