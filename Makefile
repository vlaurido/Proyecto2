proyecto2: proyecto2.c 
	gcc -Wall -g $^ -lm -o $@

.PHONY: clean
clean:
	rm -rf proyecto2
