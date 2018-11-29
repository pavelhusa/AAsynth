/**
 * Main Synth class
 * 
 * Description: Implements Synth class.
 */
 
#include "Synth.h"
#include "Config.h"
#include "fixedPointMath.h"

Synth::Synth() {
  syn_state = -1;
  syn_channel = 0;
  syn_note = 0;
  syn_velocity = 0;
};

/**
 * MIDI handling
 */
void Synth::noteOn(byte channel, byte note, byte velocity) {
  syn_state = 1;
  if(note > syn_note) {
    syn_channel = channel;
    syn_note = note;
    syn_velocity = velocity;
    syn_osc1.setNote(note);  
    syn_osc2.setNote(note);
    syn_osc2.detune(10);
    //test_osc.setNote(note);
    sub_osc.setNote(note-12);    
  }
};

void Synth::noteOff(byte channel, byte note, byte velocity) {
  if(note == syn_note && channel == syn_channel) {
    syn_state = -1;
    syn_channel = 0;
    syn_note = 0;
    syn_velocity = 0;
    syn_osc1.reset();  
    syn_osc2.reset();
    sub_osc.reset();    
  }
};
void Synth::controlChange(byte channel, byte number, byte value) {
  switch(number) {
    #ifdef OSC2_DETUNE_CC 
      case OSC2_DETUNE_CC:
        syn_osc2.detune(value);
      break;
    #endif
    #ifdef PULSE_WIDTH_CC 
      case PULSE_WIDTH_CC:
        syn_osc2.setPulseWidth(value*100/127);
      break;
    #endif
  }
}
/*
 * Mixing osclillators together
 */
inline uint16_t Synth::mix() {
  uint32_t out;
  out = syn_osc1.getSample();
  out += fixed_mul_8(syn_osc2.getSample(), OSC2_LEVEL);
  out += fixed_mul_8(sub_osc.getSample(), SUB_OSC_LEVEL);
  out >>= 1;
  //out = test_osc.getSample();
  return (out*syn_velocity)>>7;  
}
/*
 * Outputting
 */
uint16_t Synth::play() {
  return Synth::mix();
};

void Synth::updateControl() {

}
