all: proceso_usb servidor_web

proceso_usb: proceso_usb.c 
	gcc -Wall -g $^ -lm -o $@ -ludev
	
servidor_web: servidor_web.c 
	gcc -Wall -g $^ -lm -o $@ -lmicrohttpd

.PHONY: clean 
clean:
	rm -rf proceso_usb servidor_web
