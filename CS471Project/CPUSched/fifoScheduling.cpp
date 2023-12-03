#include "fifo.h" 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

// Function to read in the Datafile1.txt file
void readFile(const string &fin, queue<fifoProcess> &fifoProcesses) {
    ifstream inputFile(fin);
    // If statement for error in opening the file.
    if(!inputFile.is_open()) {
        cerr << "File cannot be opened: " << fin << endl;

        return;
    }
    // Get the first line of the text file
    // so it is not read
    string header;
    getline(inputFile, header);

    fifoProcess process;
    int counter = 0;
    // While inputFile, the first column is arrival time, 
    // second column is burst length, and the last column is priority.
    while(inputFile >> process.arrivalTime >> process.burstLength >> process.prio) {
        // wait time is equal to 0
        process.waitTime = 0.0;
        process.responseTime = -1;
        // Add data to the end of the queue as they are read in.
        fifoProcesses.push(process);
        // update the counter
        counter++;
        // if the counter is equal to 500, stop
        if(counter >= 500) {
            break;
        }
    }

    inputFile.close();
}

/*
 * Function for handling first in first out scheduling
*/
void FIFO(queue<fifoProcess> &fifoProcesses) {
    double currentTime = 0.0;
    double totalElapsedTime = 0.0;
    double completedProcesses = 0.0;
    double totalWaitTime = 0.0;
    double turnAroundTime = 0.0;
    double totalTurnAroundTime = 0.0;
    double totalBurstTime = 0.0;
    double totalResponseTime = 0.0;
    // Opening the output file for the solutions
    ofstream FIFOSolution;
    FIFOSolution.open("Output-FIFOScheduling.txt");

    while(!fifoProcesses.empty()) {
        // Point to the first element of the queue
        fifoProcess process = fifoProcesses.front();
        // Remove the element
        fifoProcesses.pop();

        // Wait time for each process
        process.waitTime = max(0.0, currentTime - process.arrivalTime);
        currentTime = max(currentTime, process.arrivalTime) + process.burstLength;
        if(process.arrivalTime > totalElapsedTime) {
            totalElapsedTime = process.arrivalTime;
        }
        // totalElapsedTime = max(totalElapsedTime, currentTime);
        completedProcesses++;

        totalElapsedTime += process.burstLength;

        // Calculating the total wait time
        totalWaitTime += process.waitTime;
        // Calculating the turn around time
        turnAroundTime = process.burstLength + process.waitTime;
        // Calculating the total turn around time
        totalTurnAroundTime += turnAroundTime;
        // Calculating the total burst length
        totalBurstTime += process.burstLength;

        process.responseTime = totalElapsedTime;

        totalResponseTime += process.responseTime;
    }
    // Outputting all the solutions into the output file
    FIFOSolution << "Completed processes: " << completedProcesses
                 << "\nTotal elapsed time: " << totalElapsedTime / 1000
                 << "\nThroughput: " << completedProcesses / (totalElapsedTime / 1000)
                 << "\nCPU Utilization: " << totalBurstTime / currentTime
                 << "\nAverage wait time: " << totalWaitTime / completedProcesses
                 << "\nAverage turn around time: " << totalTurnAroundTime / completedProcesses
                 << "\nAverage response time: " << (totalResponseTime / 1000) / completedProcesses << endl;
    
    FIFOSolution.close();
}