# CS471 Project - Problem 1

## Authors
Xavier Jordan

## Description
This program includes three scheduling algorithms written in C++ which a user can choose from. They will act as a CPU scheduler that can handle 500 simulated processes. The following are the scheduling algorithms:
* First In First Out (FIFO)
* Shortes Job First without preemption (SJF)
* Priority with preemption

## Input File
Each algorithm takes a data file named "Datafile1.txt" containing a header and 513 processes with three columns. The columns represent Arrival Time, Burst Length, and Priority in that order. Only the first 500 processes are read and stored in a queue or a vector depending on the algorithm of choice.

## Compiling The Program
**Before compiling, be sure to be in the CPUSched directory**<br>
The program can be compiled in the terminal using the following command:<br>
```g++ -std=c++11 -o program main.cpp fifoScheduling.cpp sjfScheduling.cpp priorityScheduling.cpp```

## Running The Program
**Before running, be sure to be in the CPUSched directory**<br>
To run the program, use the following command in the terminal:<br>
```./program```

## Output
There will be an output file for each program after running them.
* For FIFO: Output-FIFOScheduling.txt
* For SJF: Output-SJFScheduling.txt
* For Priority: Output-PriorityScheduling.txt

## Results, Summary, and Explanation
You can see in each output file the results of the algorithms. The completed processes, total elapsed time, throughput, and the CPU utilization were mostly the same for all. 
The SJF algorithm had the lowest average wait time, average turn around time, and the average response time out of the three algorithms.
The SJF algorithm chooses processes with the lowest burst lengths to execute, therefore making the rest of the processes wait less.