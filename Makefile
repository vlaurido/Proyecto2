proceso_usb: proceso_usb.c 
	gcc -Wall -g $^ -lm -o $@

.PHONY: clean
clean:
	rm -rf proceso_usb
