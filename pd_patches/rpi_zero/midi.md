# set up rpi + arduino

run ttymidi (in a tmux window)
`ttymidi -s /dev/ttyACM1 -n mission_control -v`

run pure data
_something like this_
`sudo pd -nogui -alsamidi -rt CBOscuino.pd`

connect midi out of pd to input of ttymidi
_see our ins and outs_
`aconnect -lio`

_connect_
`aconnect 129:0 128:1`

send midi from pure data running on pi, it goes into arduino via ttymidi
