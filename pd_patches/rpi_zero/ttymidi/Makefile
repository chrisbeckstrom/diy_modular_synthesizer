all:
	gcc src/ttymidi.c -o ttymidi -lasound
clean:
	rm ttymidi
install:
	install -m 0755 ttymidi /usr/local/bin
uninstall:
	rm /usr/local/bin/ttymidi
