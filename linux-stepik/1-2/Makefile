all: libsolution.so

libsolution.so:
	gcc -c -o libsolution.so -fPIC -shared solution.c
clean:
	rm -f *.so 2>/dev/null
