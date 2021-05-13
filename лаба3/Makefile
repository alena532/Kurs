all: Clean BuildMain 

BuildMain:
	mkdir -p bin/program
	gcc -std=c89 -o bin/program/main main.c

RunProgram:
	./bin/program/main

Clean: 
	rm -rf bin