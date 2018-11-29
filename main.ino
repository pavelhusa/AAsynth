/* Libraries */
#include <Arduino.h>
#include <SPI.h>
#include <MIDI.h>
//#include <TimerOne.h>

/* Includes */
#include "Config.h"
#include "DAC.h"
#include "Synth.h"

DAC dac(CS_PIN, LATCH_PIN);

Synth synthe;

#if DEBUG == 0
//MIDI library init
MIDI_CREATE_DEFAULT_INSTANCE();
#else 
int val = 0;
#endif


void setup()
{
  /**
   * Disable MIDI lib if debugging
   */
  #if DEBUG == 0
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(noteOn);
  MIDI.setHandleNoteOff(noteOff);
  MIDI.setHandleControlChange(controlChange);  
  Serial.begin(31250);  
  timer1Init();  
  pinsInit(); 
  #else
  Serial.begin(9600);  
  synthe.noteOn(0, 69, 127);
  synthe.test_osc.setNote(69);
  Serial.println(synthe.test_osc.osc_increment);
  synthe.test_osc.detune(-127);
  Serial.println(synthe.test_osc.osc_increment);
  #endif
}

void timer1Init() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  //16000000/32768 - 1
  OCR1A = 968;

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void pinsInit() {
}

void loop()
{
  mainHook();
}


ISR(TIMER1_COMPA_vect) {
  dac.writeData(synthe.play());
}

void mainHook() {
  #if DEBUG == 0   
  MIDI.read();
  synthe.updateControl();
  #else
  val = analogRead(A1);
  //Serial.println(val);
  delay(500);
  #endif
}

void noteOn(byte channel, byte note, byte velocity) {
  if(note >= MIDI_NOTE_RANGE_MIN && note <= MIDI_NOTE_RANGE_MAX) { 
    synthe.noteOn(channel, note, velocity);
  }
}

void noteOff(byte channel, byte note, byte velocity) {
  if(note >= MIDI_NOTE_RANGE_MIN && note <= MIDI_NOTE_RANGE_MAX) {
    synthe.noteOff(channel, note, velocity);
  }
}
void controlChange(byte channel, byte number, byte value) {
  synthe.controlChange(channel, number, value);
}
/*
void pitchBend(byte channel, int bend) {
  synthe.pitchBend(channel, bend);
}
*/
