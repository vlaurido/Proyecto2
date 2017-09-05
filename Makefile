all: servidor_web proceso_daemon

usb_daemon: objects
	gcc -Wall -Llib/ /obj/proceso_daemon.o obj/funciones_usb.o -o /bin/proceso_daemon

proceso_daemon: ./src/proceso_daemon.c
	gcc -Wall -Iinclude/ -c -g src/proceso_daemon.c -o obj/proceso_daemon.o

servidor_web: ./src/servidor_web.c
		gcc -Wall ./src/servidor_web.c -lmicrohttpd -o ./bin/servidor_web

objects:
	gcc -Wall -Iinclude/ -c src/funciones_usb.c -o obj/funciones_usb.o

libusb: ./src/funciones_usb.c
	gcc -Wall -Iinclude/ -shared -fPIC src/funciones_usb.c -o lib/libusb.so

.PHONY: clean
clean:
	rm -rf obj/*.o bin/*
