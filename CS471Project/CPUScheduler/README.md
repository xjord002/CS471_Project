# CS471 Project - Problem 1

## Authors
Xavier Jordan

## Description
This program includes three scheduling algorithms which a user can choose from. They will act as a CPU scheduler that can handle 500 simulated processes. The following are the scheduling algorithms:
* First In First Out (FIFO)
* Shortes Job First without preemption (SJF)
* Priority with preemption

## Input File
Each algorithm takes a data file named "Datafile1.txt" containing a header and 513 processes with three columns. The columns represent Arrival Time, Burst Length, and Priority in that order. Only the first 500 processes are read and stored in a queue or a vector depending on the algorithm of choice.

## Compiling The Program
**Before compiling, be sure to be in the CPUScheduler directory**<br>
The program can be compiled in the terminal using the following command:
```g++ -std=c++11 -o program main.cpp fifoScheduling.cpp sjfScheduling.cpp priorityScheduling.cpp```

## Running The Program
**Before running, be sure to be in the CPUScheduler directory**<br>
To run the program, use the following command in the terminal:
```./program```

## Output
There will be an output file for each program after running them.
* For FIFO: Output-FIFOScheduling.txt
* For SJF: Output-SJFScheduling.txt
* For Priority: Output-PriorityScheduling.txt

## Results, Summary, and Explanation
