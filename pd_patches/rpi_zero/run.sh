#!/bin/bash

# RUN
# script to get the Raspberry Pi Zero + Arduino module up and running
# for use with my DIY modular synthesizer
# chrisbeckstrom.com
# Chris Beckstrom - 2018-01-16

# what this script does:
# - kills any existing ttymidi or pure data sessions
# - runs ttymidi and pure data in new tmux sessions (detached)
# - connects pd and ttymidi i/o

# why?
# so I can run a single script to get my pure data + arduino module running

echo "starting up Rpi+Arduino"

echo "killing existing ttymidi and pd sessions"
sudo killall ttymidi && sudo killall pd

# full path to the pure data file
patch='/home/pi/diy_modular_synthesizer/pd_patches/rpi_zero/rpi.pd'

# which audio devices to use? (use `pd -nogui -listdev` to see what's available)
# TODO: arrive at these numbers programmatically the way we do with midi devices below
audioin='3'
audioout='3'

# which midi devices to use? (use -listdev as above)
midiin='1'
midiout='1'

# what should we name the arduino midi device?
arduinoName='mission_control'

# where is the arduino?
arduinoDev='/dev/ttyACM1' # i.e. '/dev/ttyACM0'

# create a tmux session for ttymidi (and use custom tmux configuration file)
tmux -f /home/pi/.tmux/tmux.conf new -s ttymidi -d

# start ttymidi alsa midi -> serial -> arduino bridge (in that tmux session)
echo "starting ttymidi"
echo "ttymidi -s $arduinoDev -v -n $arduinoName"
tmux send-keys -t ttymidi "ttymidi -s $arduinoDev -v -n $arduinoName" ENTER

# create a tmux session for pure data
tmux -f /home/pi/.tmux/tmux.conf new -s puredata -d

echo "pure data info:"
echo "audio in dev: $audioin"
echo "audioout dev: $audioout"
echo "midiindev: $midiin"
echo "midioutdev: $midiout"
echo "patch: $patch"

echo "--- starting pd --"

# start the PD patch and keep it in the foreground
tmux send-keys -t puredata "sudo pd -nogui -alsamidi -rt -audioindev $audioin -audiooutdev $audioout -midiindev $midiin -midioutdev $midiout $patch" ENTER

sleep 2 # wait for pd to connect to alsa

# find the alsa device number of ttymidi
echo "finding the alsa device number of ttymidi..."
# holy crap I love unix text manipulation...!!
ttymidiDev=$(aconnect -lio | grep "$arduinoName" | cut -f1 -d ":" | sed 's/.* //')
echo "we think it's:"
echo $ttymidiDev

# find the alsa device umber of puredata
echo "finding the alsa device number of puredata..."
pdDev=$(aconnect -lio | grep "Pure Data" | cut -f1 -d ":" | head -n +1 | sed 's/.* //')
echo "we think it's:"
echo $pdDev

# connect midi ports
## pd midi out -> arduino midi in
echo "connecting pd's midi output to the arduino's midi input"
aconnect $pdDev:1 $ttymidiDev:1

## arduino midi out -> pd midi in
echo "connecting the arduino's midi output to pd's midi input"
aconnect $ttymidiDev:0 $pdDev:0

# done!
echo "All set!"



