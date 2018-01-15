#include <MIDI.h>
/*
  This example is a modified version of Basic I/O MIDI tutorial
  by Franky. It tries to demonstrate how to use Arduino MIDI
  library together with ttyMIDI. You will need to install
  Arduino MIDI library for this to work:
  
  http://www.arduino.cc/playground/Main/MIDILibrary
  
  All example patches shipped with the Arduino MIDI library
  will work with ttyMIDI with same change (if they wont, please
  report a bug).
  
*/

#define LED 13   		// LED pin on Arduino board

void setup() {
  pinMode(LED, OUTPUT);
  MIDI.begin(4);            	// Launch MIDI with default options
				// input channel is set to 4
  
  /* Now the problem is that serial port at the computer is only
     able to read serial data at 'standard' baud rates. MIDI baud rate
     that Arduino MIDI library is using, is not one of these.
     One way of fixing this is to edit line 54 of file MIDI.h and set
     Arduino MIDI library to use some other baud rate.
    
     However, one can just simply change the baud rate
     of serial line to some standard baud rate by calling Serial.begin(int)
     immediately after calling MIDI.begin(int). Here we set the speed
     to default baud rate of ttymidi, 115200! This is all you need to
     remember to do if you want to read the data with ttymidi running
     on your computer.  
   */
  Serial.begin(115200);
}

void loop() {
  if (MIDI.read()) {
    digitalWrite(LED,HIGH);     // Blink the LED
    MIDI.sendNoteOn(42,127,1);  // Send a Note (pitch 42, velo 127 on channel 1)
    delay(1000);		// Wait for a second
    MIDI.sendNoteOff(42,0,1);   // Stop the note
    digitalWrite(LED,LOW);    	
  }
}
