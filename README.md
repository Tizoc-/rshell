RSHELL
===
LICENSE INFO
---
Project Source can be downloaded from https://github.com/Tizoc-/rshell.git
----


Summary
---
My attempt at my own rshell bash terminal that passes bin commands which supports multiple arguments in commands, comments, and exit from the terminal.This repo also now come with its own ls command that supports diplaying directory contents and information.
This was accomplished using the stat and opendir readdir and closedir function calls(also one instance of the readlink syscall).

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
ls can display contents of a directory 
ls can show permissions
ls can display regular and sybolic link file
ls can display hiddens files 


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

Bugs ls
---
the recursion and optional file arguments dont work

if an invalid file is passed a segmentation fault occurs  

symbolic links dont show contets of directory it is pointing to

not all combinations of flags work with symobilic links

not formatted properly

Bug io
---
after running any number of io redirections the regular bash commands such as cat, ls ,pwd without redirection doesnt not work

piping doesnt work

when more that one of the io redirection on the first one is taken into account

passing in nothing causes segmentation fault
