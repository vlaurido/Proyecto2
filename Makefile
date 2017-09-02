all: proceso_usb servidor_web

proceso_usb: ./src/proceso_usb.c 
	gcc -Wall -g src/proceso_usb.c -lm -o bin/proceso_usb -ludev
	
servidor_web: ./src/servidor_web.c 
	gcc -Wall -g src/servidor_web.c -lm -o bin/servidor_web -lmicrohttpd

.PHONY: clean 
clean:
	rm -rf bin/*
