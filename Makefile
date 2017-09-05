all: servidor_web proceso_daemon

proceso_daemon: objects
	gcc -Wall -Iinclude/ obj/*[!1].o -ludev -o bin/proceso_daemon

servidor_web: ./src/servidor_web.c
		gcc -Wall ./src/servidor_web.c -lmicrohttpd -o ./bin/servidor_web

objects: ./src/funciones_usb.c src/proceso_daemon.c
	gcc -Wall -Iinclude/ -c src/proceso_daemon.c -o obj/proceso_daemon.o -ludev
	gcc -Wall -Iinclude/ -c src/funciones_usb.c -o obj/funciones_usb.o -ludev


.PHONY: clean
clean:
	rm -rf obj/*.o bin/*
