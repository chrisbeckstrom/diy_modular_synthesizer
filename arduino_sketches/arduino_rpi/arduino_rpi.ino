// http://www.deadpixel.ca/arduino-osc/
// https://github.com/davidbouchard/arduino-osc

// use in conjunction with
// pd patch

#include <OscSerial.h>
#include <EthernetUdp.h>
#include <SPI.h>  
 
OscSerial oscSerial;
long timer; // not sure we need this anymore

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
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}
 
void loop() {
  
  // READ ANALOG INPUTS and send to PD via OSC messages over serial

  // TODO: make a nice function for this
  OscMessage a0("/a0");
  a0.add(analogRead(A0));
  oscSerial.send(a0);

  //OscMessage a1("/a1");
  //a1.add(analogRead(analog1));
  //oscSerial.send(a1);

  //OscMessage a2("/a2");
  //a2.add(analogRead(analog2));
  //oscSerial.send(a2);

  //OscMessage a3("/a3");
  //a3.add(analogRead(analog3));
  //oscSerial.send(a3);

  //OscMessage a4("/a4");
  //a4.add(analogRead(analog4));
  //oscSerial.send(a4);

  //OscMessage a5("/a5");
  //a5.add(analogRead(analog5));
  //oscSerial.send(a5);
  
  // important! 
  oscSerial.listen();

  
   
}


// create actions for each of the gate/trigger pins 


void oscEvent(OscMessage &m) { // *note the & before msg
  // receive osc messages

  // top row: turn each pin on or off by sending /number 0|1
  // i.e. `/2 1` will turn pin #2 on (make it go HIGH)
  m.plug("/2", two);
  m.plug("/4", four);
  m.plug("/7", seven);
  m.plug("/8", eight);
  m.plug("/12", twelve); 
  m.plug("/13", thirteen); 
}
void two(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(2, LOW);
  if (value == 1) digitalWrite(2, HIGH);
}

void four(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(4, LOW);
  if (value == 1) digitalWrite(4, HIGH);
}

void seven(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(7, LOW);
  if (value == 1) digitalWrite(7, HIGH);
}


void eight(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(8, LOW);
  if (value == 1) digitalWrite(8, HIGH);
}

void twelve(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(12, LOW);
  if (value == 1) digitalWrite(12, HIGH);
}
void thirteen(OscMessage &m) {  // *note the & before msg
  // getting to the message data 
  int value = m.getInt(0); 
  if (value == 0) digitalWrite(13, LOW);
  if (value == 1) digitalWrite(13, HIGH);
}


