Authors: Ian Ordonez, Daniel Gonzalez (Group 18)
Assignment: HW1 
Class: COP 3402 Fall 0001

## Introduction
This README file provides instructions on how to compile and run the PM/0 virtual machine (VM) implemented in C.

## Compilation
To compile the PM/0 VM, follow these steps:

1. Open a terminal window.

2. Navigate to the directory where you have saved the source code file (`vm.c`) and the input ELF file (`input.txt`).

3. Compile the program using the `gcc` compiler:
    gcc -o vm vm.c

## Run
To run the PM/0 VM with the ELF input file, run the following command in the terminal after compilation:
    ./vm input.txt