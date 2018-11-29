/**
 *  Based on: Arduino for Musicians
 *  Brent Edstrom, 2013
 * 
 *  Author: Pavel Husa
 *  
 *  Desc: Implementation of different waveshapes.
 */

#include "Oscillator.h"
//NOT COMPILED WITHOUT IT
#include "Config.h"

class sawOscillator: public Oscillator {
  public:
  
  inline virtual uint32_t getSample() {
      return ((uint32_t)Oscillator::getSample() >> 20);
  }
};

class invSawOscillator: public Oscillator {
  public:
  
  inline virtual uint32_t getSample() {
    return ((uint32_t)(MAX_INT32_VAL - Oscillator::getSample()) >> 20);
  }
};

class triangleOscillator: public Oscillator {
  public:
    inline virtual uint32_t getSample() {
      uint32_t sample = Oscillator::getSample();
      if(sample < MAX_INT32_VAL>>1) {
        return sample >> 19;
      }
      else {
        return (MAX_INT32_VAL-sample) >> 19;
      }
    }
};

class pulseOscillator: public Oscillator {
  private:
  uint32_t pulse_width;
  public:
  
  pulseOscillator():Oscillator(){
    pulse_width = DEFAULT_PULSE_WIDTH;
  }
  
  //Set width in percentage
  void setPulseWidth(unsigned char width) {
    pulse_width = MAX_INT32_VAL * width / 100;
  }

  inline virtual uint32_t getSample() {
    if(Oscillator::getSample() < pulse_width) {
      return MAX_AMPLITUDE;
    }
    else {
      return 0;
    }
  }
};

//This can be obviously done by set pulse width to 50%
class squareOscillator: public Oscillator {
  public:  
  inline virtual uint32_t getSample() {
    if(Oscillator::getSample() < MAX_INT32_VAL>>1) {
      return MAX_AMPLITUDE;
    }
    else {
      return 0;
    }  
  }
};

class sineOscillator: public Oscillator {
  public:  
  inline virtual uint32_t getSample() {
    return (uint16_t)pgm_read_dword_near(sineWaveTable + (Oscillator::getSample()>>22));   
  }
};

class noiseGenerator: public Oscillator {
  private:
  uint32_t last_sample;
  public:
  
  noiseGenerator() {last_sample = RANDOM_SEED_START;}
  
  inline virtual uint32_t getSample() {
    last_sample = (RANDOM_SEED_A * last_sample + RANDOM_SEED_B);
    return last_sample >> 20;
  }
};
