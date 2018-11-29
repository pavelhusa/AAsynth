/**
 * Based od Arduino for Musicians
 * Brent Edstrom, 2013
 * 
 *  Author: Pavel Husa
 *  
 *  Description: Implements Oscillator class. Different shapes.
 */
 
#include "Oscillator.h"
#include "fixedPointMath.h"

/*
 * Constructor init.
 */
Oscillator::Oscillator() {
  osc_accumulator = 0;
  osc_increment = 0;
  osc_note = 0;
  osc_detune = 0;
};

void Oscillator::reset() {
  osc_accumulator = 0;
  osc_increment = 0;
  osc_note = 0; 
}
/*
 * Set increment from MIDInote-to-frequency-to-increment table.
 */
void Oscillator::setNote(unsigned char n) {
  if(osc_detune==0) {
    osc_increment = pgm_read_dword_near(incFreqTable + n);
  }
  else {
    Oscillator::detune(osc_detune);
  }
  osc_note = n;
};

void Oscillator::detune(unsigned char detune) {
  osc_detune = detune;
  uint32_t a = pgm_read_dword_near(incFreqTable + osc_note);
  uint32_t b;
  if(detune == 0) {
    osc_increment = a;
    return;           
  }
  /*
  else if(detune < 0) {
    b = a;
    a = pgm_read_dword_near(incFreqTable + osc_note - 1);
    detune+=127<<1;   
    osc_increment = b-((detune)*(b-a)/63); 
  }*/
  else {
    b = pgm_read_dword_near(incFreqTable + osc_note + 1);  
    osc_increment = a+((detune)*(b-a)/127);  
  }
};
