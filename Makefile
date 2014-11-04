all:
	[ -d ./bin ] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11  src/main.cpp -o bin/main 
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/cp.cpp -o bin/cp
shell:
	[ -d ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/main.cpp -o bin/main
cp:
	[ -d ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/cp.cpp -o bin/cp
