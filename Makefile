all:
	[ -e ./bin ] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11  src/rshell.cpp -o bin/rshell
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/cp.cpp -o bin/cp
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/ls.cpp -o bin/ls
rshell:
	[ -e ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/main.cpp -o bin/main
cp:
	[ -e ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/cp.cpp -o bin/cp
ls:
	[ -e ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/ls.cpp -o bin/ls

