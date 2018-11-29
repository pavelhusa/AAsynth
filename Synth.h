/**
 * Main Synth class
 * 
 * Description: Puts all together. Oscillators, mixer, filter.
 * 
 * Author: Pavel Husa
 */

#ifndef SYNTH_ENGINE
#define SYNTH_ENGINE

#include <Arduino.h>
#include "Oscillator.h"
#include "OscillatorTypes.h"

class Synth {
  //triangleOscillator syn_osc1;
  //sawOscillator syn_osc1;
  //invSawOscillator syn_osc1;
  //pulseOscillator syn_osc1;
  sineOscillator syn_osc1;
  //squareOscillator syn_osc1;
  //pulseOscillator syn_osc1;
  //noiseGenerator syn_osc1;
  sineOscillator syn_osc2;
  //triangleOscillator syn_osc2;
  //sawOscillator syn_osc2;
  //invSawOscillator syn_osc2;
  //pulseOscillator syn_osc2;
  //squareOscillator syn_osc2;
  
  squareOscillator sub_osc;
  
  uint16_t mix();
  void synthInit();
  
  char syn_state;
  unsigned char syn_channel;
  unsigned char syn_note;
  unsigned char syn_velocity;

  public:
  Synth();
  uint16_t play();
  //sineOscillator test_osc;

  //void pitchBend(byte channel, int bend);
  void controlChange(byte channel, byte number, byte value);
  void noteOn(byte ch, byte n, byte v);
  void noteOff(byte ch, byte n, byte v);
  void updateControl();
};

#endif
