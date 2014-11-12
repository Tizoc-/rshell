all:
	[ -d ./bin ] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11  src/main.cpp -o bin/main 
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/cp.cpp -o bin/cp
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/ls.cpp -o bin/ls
shell:
	[ -d ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/main.cpp -o bin/main
cp:
	[ -d ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/cp.cpp -o bin/cp
ls:
	[ -d ./bin] || mkdir bin
	g++ -Wall -Werror -ansi -pedantic -std=c++11 src/ls.cpp -o bin/ls

