all:
	gcc src/*.c -I include/ -o pl0-compiler

clean:
	rm -rf pl0-compiler
	rm -rf *.out
