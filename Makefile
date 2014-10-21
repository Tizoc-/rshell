all:
	[ -e ./bin ] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic main.cpp  ./src/main.cpp -o ./bin/main 

