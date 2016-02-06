/*

   CB ARDUINO OSCILLATOR
   Mostly copied and pasted from various examples in the 
   fantastic Mozzi Arduino library
   This particular sketch is built on the "piezo" example

  PURPOSE (short version):
  - So far I haven't been able to create any analog 
  1V/oct oscillators or exponential converters, so my plan
  B is to build a digital, MIDI-controlled oscillator.

   PURPOSE (more details):
   - Receive MIDI note info (pitch, velocity, etc)
   - Generate waveforms based on that pitch
   - "listen" to analog input in the form of voltage
    (control voltage) and potentiometers to change
    the oscillator pitch and possibly digital waveshaping
   - Possibly do other cool stuff like have a wavetable
    library that can be modulated via CV

   ---
   
   Example using a piezo to change the frequency of a sinewave
   with Mozzi sonification library.
   
   Demonstrates the use of Oscil to play a wavetable, and analog input for control.
   
   This example goes with a tutorial on the Mozzi site:
   http://sensorium.github.io/Mozzi/learn/introductory-tutorial/
   
   The circuit:
     Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or 
     check the README or http://sensorium.github.com/Mozzi/
   
     Piezo on analog pin 3:
       + connection of the piezo attached to the analog pin
       - connection of the piezo attached to ground
       1-megohm resistor between the analog pin and ground
   
   Mozzi help/discussion/announcements:
   https://groups.google.com/forum/#!forum/mozzi-users
   
   Tim Barrass 2013, CC by-nc-sa.
*/

//#include <ADC.h>  // Teensy 3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h> // oscillator 
#include <WaveShaper.h>
// OSCILLATOR WAVETABLES
#include <tables/sin2048_int8.h> // table for Oscils to play
#include <tables/triangle2048_int8.h> // nice triangle
#include <tables/saw8192_int8.h> // nice saw
#include <Smooth.h>
// WAVESHAPING WAVETABLES
#include <tables/waveshape_chebyshev_3rd_256_int8.h>
#include <tables/waveshape_chebyshev_6th_256_int8.h>
#include <tables/waveshape_compress_512_to_488_int16.h>
#include <tables/waveshape_chebyshev_4th_256_int8.h>
#include <tables/waveshape1_softclip_int8.h>
#include <tables/waveshape2_softerclip_int8.h>
#include <tables/waveshape_tanh_int8.h>

// debug?
int debug = 0;

// increase the rate of updateControl from the default of 64, to catch the piezo's rapid transients
#define CONTROL_RATE 128      // original: 128
#define POWER 256
int alpha = 178;

const int FREQUENCY_PIN = 0;  // set the analog input pin for the frequency modulation 
const int WAVESHAPE_PIN = 1; // set the analog pin for waveshaping modulation

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
//Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> Oscillator1(SIN2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> Oscillator1(TRIANGLE2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aGain1(SIN2048_DATA); // to fade sine wave in and out before waveshaping
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aGain2(SIN2048_DATA); // to fade sine wave in and out before waveshaping

// WAVESHAPERS
WaveShaper <char> aCheby3rd(CHEBYSHEV_3RD_256_DATA); // 5th harmonic
WaveShaper <char> aCheby4th(CHEBYSHEV_4TH_256_DATA); // 4th harmonic
WaveShaper <char> aCheby6th(CHEBYSHEV_6TH_256_DATA); // 8th harmonic
WaveShaper <char> softclip(WAVESHAPE1_SOFTCLIP_DATA); //
WaveShaper <char> saw(SAW8192_DATA); //
WaveShaper <char> softerclip(WAVESHAPE2_SOFTERCLIP_DATA);
WaveShaper <char> tanny(WAVESHAPE_TANH_DATA);

WaveShaper <int> aCompress(WAVESHAPE_COMPRESS_512_TO_488_DATA); // to compress instead of dividing by 2 after adding signals

// control variable for waveshape
byte waveshapeControl = 0;

void setup(){
  //Serial.begin(9600); // for Teensy 3.1, beware printout can cause glitches
  Serial.begin(115200); // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the piezo values
  startMozzi(CONTROL_RATE); // :)) use the control rate defined above
  aGain1.setFreq(1.f);    //use a float for low fq in setup it doesn't need to be fast // WAVESHAPING RATE
  //aGain2.setFreq(.4f);
  //int waveshape_value = 255;
}


void updateControl(){
  // READ FREQUENCY_PIN to change frequency of Oscillator1
  int frequency_value = mozziAnalogRead(FREQUENCY_PIN); // value is 0-1023
  int frequency = frequency_value*3; // calibrate
  
  // this part is just for debugging
  if ( debug == 1 ) {
      Serial.print("FREQUENCY_PIN value = ");
      Serial.print((int)frequency);
      Serial.print(" | ");
  }

  // change the frequency of the sine oscillator based on the FREQUENCY_PIN
  Oscillator1.setFreq(frequency);

  // READ WAVESHAPE_PIN to change waveshape of the.. waveshaper
  int waveshaper_value = mozziAnalogRead(WAVESHAPE_PIN);  // value is 0-1023
  int waveshape = waveshaper_value; // calibrate
  // map it to an 8 bit range for efficient calculations in updateAudio()
  waveshapeControl = map(waveshape, 0, 1023, 0, 200);
  
   // this part is just for debugging
   if ( debug == 1 ) {
        Serial.print("WAVESHAPE_PIN value = ");
        Serial.print((int)waveshapeControl);
        Serial.print("\n");
   }

  //waveshapeControl = waveshape;
  
}


int updateAudio(){
  //return Oscillator1.next();
  char asig0 = Oscillator1.next(); // sine wave source, the thing that is being waveshaped
  
  // WAVESHAPING STUFF
  // offset the signals by 128 to fit in the 0-255 range for the waveshaping table lookups
  byte aGain1 = waveshapeControl;   // this is what controls the amount of waveshaping

  // control the volume/mix of the waveshaping tables
  byte asig1 = (byte)128+((asig0*((byte)128+aGain1))>>8);   
  byte asig2 = (byte)128+((asig0*((byte)128+aGain1))>>8);
  byte asig3 = (byte)128+((asig0*((byte)128+aGain1))>>8);
  byte asig4 = (byte)128+((asig0*((byte)128+aGain1))>>8);
  byte asig5 = (byte)128+((asig0*((byte)128+aGain1))>>8);
  
  // get the waveshaped signals
  char awaveshaped1 = softclip.next(asig1);
  char awaveshaped2 = aCheby3rd.next(asig2);
  char awaveshaped3 = aCheby6th.next(asig3);
  char awaveshaped4 = softerclip.next(asig4);
  char awaveshaped5 = tanny.next(asig5);
  
  // use a waveshaping table to squeeze 2 summed 8 bit signals into the range -244 to 243
  // notes:
  //      softclip + cheby6th = nice, sort of round, rough triangle
  //      softerclip + cheby6th even nicer! closer to triangle when waveshape level is all the way down
  int awaveshaped666 = aCompress.next(256u + awaveshaped3 + awaveshaped5);
  return awaveshaped666;
  //return Oscillator1.next();    // this just gives you the plain old Oscillator1, no waveshaping
}


void loop(){
  audioHook();
}
