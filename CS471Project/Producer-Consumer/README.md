# CS471 Project - Problem 2

## Authors
Xavier Jordan

## Description
This program uses Pthreads to solve the producer-consumer problem. This program is written in C++. The program will take an input file with a few lines of data to compute the turnaround time.

## Input Files
The program will take three seperate files containing 12 producers and 12 consumers in each file. The files included are:
*input-2sec-wait.txt
*input-4sec-wait.txt
*input-6sec-wait.txt
Each file has a column with sleep times matching the #sec in their names.

## Compiling The Program
**Before compiling, be sure to be in the Producer-Consumer directory**<br>
The program can be compiled with the following command in the terminal:<br>
```g++ -std=c++11 -o program main.cpp```

## Running The Program
**Before running, be sure to be in the Producer-Consumer directory**<br>
To run the program, use the following command in the terminal:<br>
```./program [input file]```

## Output
There will be an output file to match the input file that was used to run the program:<br>
*For input-2sec-wait.txt it will be output-2sec-wait.txt
*For input-4sec-wait.txt it will be output-4sec-wait.txt
*For input-6sec-wait.txt it will be output-6sec-wait.txt

## Results, Summary, and Explanation