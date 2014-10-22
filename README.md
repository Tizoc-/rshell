RSHELL
===
LICENSE INFO
---
Project Source can be downloaded from https://github/Tizoc-/rhsell.git
----

Author & Contributor List
---------------
Paul Alvarez

File List
--------

Makefile

LICENSE

README

./src

./tests

/src

main.cpp

./tests

exec.script


Summary
---
My attempt at my own rshell bash terminal that passes bin commands which supports multiple arguments in commands, comments, and exit from the terminal.


How to run
---
To run this you first need to clone

https://github.com/Tizoc-/rshell.git

cd rshell

git checkout hw0

make

bin/rshell


Features
---
Able to run mutliple commands with one or more arguments
able to exit out of shell
can comment out lines

Bug
---
when an invalid command is entered exit need to be pressed twice to exit shell

connecters(;,&&,||) dont work

input needs to have spaces so it can  parse correctly

when an invalid command is entered need to press the exit command the amount of times a invalid command was entered

although the # comments out the line and commands it show ups a an invalid command

hostname doesnt show up correctly in script

if a connecter or comment is nest to a command it wont read it

argument array limited to 100

username and  hostname displayed
