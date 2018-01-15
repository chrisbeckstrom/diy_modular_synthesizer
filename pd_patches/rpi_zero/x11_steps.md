
1. xauth list | grep unix`echo $DISPLAY | cut -c10-12` > /tmp/xauth
2. sudo su
3. xauth add `cat /tmp/xauth`
