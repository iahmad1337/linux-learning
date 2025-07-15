all: libsolution.so

libsolution.so:
	gcc solution.c -c -fPIC -shared -o libsolution.so
clean:
	rm -f *.so 2>/dev/null
