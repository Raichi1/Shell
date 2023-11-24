# Shell
## Index
- [Shell](#Shell)
	- [Índice](#Index)
	- [Description](#Description)
 	- [Features](#Features) 
	- [Requirements](#Requirements)
## Description
A shell is a command-line interface that serves as an intermediary between the user and the operating system, allowing users to interact with the system by executing commands. It provides a way to launch programs, manage files, and perform various tasks by interpreting user input. Shells can offer scripting capabilities, customization through configuration files, and access to a wide range of system utilities, making them a fundamental component of operating systems for both novice and advanced users.
## Features
Run the main program and you can access the shell functionalities. For example, you can move between folders, list documents, create folders, files, etc. In addition, by entering the command '<block>' you can execute loops, functions, conditional structures, etc. Finally, you can define the variables you are going to work with.
## Requirements
To run the program you need to have cmake, llvm 17, cplusplus and antlr4.
## USE
First, you need to go to the folder containing the .g4 file. Then, run the antlr4 (.g4) file with the following command:

	```bash
 
	antlr4 -no-listener -visitor -o libs -Dlanguage=Cpp *.g4
 
	```
