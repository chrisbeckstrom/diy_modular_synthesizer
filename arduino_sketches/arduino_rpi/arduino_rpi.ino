// http://www.deadpixel.ca/arduino-osc/
// https://github.com/davidbouchard/arduino-osc

// use in conjunction with
// pd patch

#include <OscSerial.h>
#include <EthernetUdp.h>
#include <SPI.h>  
 
OscSerial oscSerial;
long timer;

// set up variables for pin values
int analog0 = A0;
int analog1 = A1;
int analog2 = A2;
int analog3 = A3;
int analog4 = A4;
int analog5 = A5;



 
void setup() {
  Serial.begin(115200); //115200
  oscSerial.begin(Serial); 

  // output pins
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // set up analog input pins
  pinMode(analog0, INPUT);
  pinMode(analog1, INPUT);
  pinMode(analog2, INPUT);
  pinMode(analog3, INPUT);
  pinMode(analog4, INPUT);
  pinMode(analog5, INPUT);
}
 
void loop() {
  
  // READ ANALOG INPUTS and send to PD via OSC messages over serial

  // TODO: make a nice function for this
  OscMessage a0("/a0");
  a0.add(analogRead(analog0));
  oscSerial.send(a0);

  OscMessage a1("/a1");
  a1.add(analogRead(analog1));
  oscSerial.send(a1);

  OscMessage a2("/a2");
  a2.add(analogRead(analog2));
  oscSerial.send(a2);

  OscMessage a3("/a3");
  a3.add(analogRead(analog3));
  oscSerial.send(a3);

  OscMessage a4("/a4");
  a4.add(analogRead(analog4));
  oscSerial.send(a4);

  OscMessage a5("/a5");
  a5.add(analogRead(analog5));
  oscSerial.send(a5);
  
  // important! 
  oscSerial.listen();

  
   
}
 
void oscEvent(OscMessage &m) { // *note the & before msg
  // receive a message 
  m.plug("/led", ledFunction); 
}

void ledFunction(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(13, LOW);
  if (value == 1) digitalWrite(13, HIGH);
}

