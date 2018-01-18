# Programs

## Program 00 (0 0 0 0)

Gate/trig outputs 

first 4: 4 voice gate sequencer outputs
5th: reset (downbeat of bar)
6th: 16ths


PWM outputs

3 = clocked random voltages
5 = clocked random voltages


Analog inputs A0-A2


Analog triggers A3-A5

A3 = trigger clocked random voltages on 3
A4 = trigger clocked random voltages on 5


Audio output LEFT

drum sounds (sequenced by gate sequencer)


Audio output RIGHT


## Program 01 (1 0 0 0)

Gate/trig outputs 


PWM outputs



Analog inputs A0-A2
A0 = sampler playback speed (pitch)


Analog triggers A3-A5
A3 = trigger/play sample
A4 = record sample


Audio output LEFT

sampler


Audio output RIGHT

white noise


## template

Gate/trig outputs 


PWM outputs


Analog inputs A0-A2


Analog triggers A3-A5


Audio output LEFT


Audio output RIGHT


## pins

PWM outputs

int pin3 = 3;
int pin5 = 5;
int pin6 = 6;
int pin9 = 9;
int pin10 = 10;
int pin11 = 11;

