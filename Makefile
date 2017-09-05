all: proceso_usb servidor_web proceso_daemon

proceso_usb: objects
	gcc -Wall ./obj/proceso_usb.o -ludev -o ./bin/proceso_usb

proceso_daemon: objects
	gcc -Wall ./obj/proceso_daemon.o -o ./bin/proceso_daemon

servidor_web: objects
	gcc -Wall ./obj/servidor_web.o -lmicrohttpd -o ./bin/servidor_web

objects:
	gcc -Wall -Iinclude/ -c src/proceso_usb.c -o obj/proceso_usb.o
	gcc -Wall -Iinclude/ -c src/proceso_daemon.c -o obj/proceso_daemon.o
	gcc -Wall -Iinclude/ -c src/servidor_web.c -o obj/servidor_web.o

.PHONY: clean
clean:
	rm -rf bin/*
