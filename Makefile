all:
	gcc src/*.c -I include/ -o pl0-compiler

run:
	./pl0-compiler pl0_examples/meu_programa.pl0 log_file.txt

clean:
	rm -rf pl0-compiler
	rm -rf *.out
