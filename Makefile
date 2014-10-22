all:
	[ -d ./bin ] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic  src/main.cpp -o bin/main 
shell:
	[ -d ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o bin.main
