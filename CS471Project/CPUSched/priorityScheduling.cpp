#include "prio.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
 
using namespace std;

// Function to read in the Datafile1.txt file
void readFile(const string &fin, vector<prioProcess> &prioProcesses) {
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

    prioProcess process;
    int counter = 0;
    // While inputFile, the first column is arrival time, 
    // second column is burst length, and the last column is priority.
    while(inputFile >> process.arrivalTime >> process.burstLength >> process.prio) {
        // wait time is equal to 0
        process.waitTime = 0.0;
        process.responseTime = -1.0;
        // Add data to the end of the queue as they are read in.
        prioProcesses.push_back(process);
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
 * Function to compare priorities and arrival times
*/
bool comparePrio(prioProcess& a, prioProcess& b) {
    // if the arrival time of the current process is equal to the previous, return the one with the higher priority
    if(a.arrivalTime == b.arrivalTime) {
        return a.prio < b.prio;
    }
    // otherwise return the arrival time that comes before
    return a.arrivalTime < b.arrivalTime;
}

/*
 * Function to handle priority scheduling with preemption
*/
void PRIO(vector<prioProcess> &prioProcesses) {
    int n = prioProcesses.size();
    double totalElapsedTime = 0.0;
    double completedProcesses = 0.0;
    double totalWaitTime = 0.0;
    double turnAroundTime = 0.0;
    double totalTurnAroundTime = 0.0;
    double totalBurstTime = 0.0;
    double totalResponseTime = 0.0;
    // Output file to store the solutions
    ofstream PrioSolution;
    PrioSolution.open("Output-PriorityScheduling.txt");
    // sorting the vector with the previous comparing function
    sort(prioProcesses.begin(), prioProcesses.end(), comparePrio);

    for(prioProcess& process : prioProcesses) {
        if(process.arrivalTime > totalElapsedTime) {
            totalElapsedTime = process.arrivalTime;
        }
        if(process.responseTime == -1.0) {
            process.responseTime = totalElapsedTime;
        }

        process.waitTime = totalElapsedTime - process.arrivalTime;
        totalWaitTime += process.waitTime;
        totalElapsedTime += process.burstLength;
        turnAroundTime = totalElapsedTime - process.arrivalTime;
        totalTurnAroundTime += turnAroundTime;
        totalBurstTime += process.burstLength;
        totalResponseTime += process.responseTime;
        completedProcesses++;
    }

    // Outputting all the solutions into the output file
    PrioSolution << "Completed processes: " << completedProcesses
                 << "\nTotal elapsed time: " << totalElapsedTime / 1000
                 << "\nThroughput: " << completedProcesses / (totalElapsedTime / 1000)
                 << "\nCPU Utilization: " << totalBurstTime / totalElapsedTime
                 << "\nAverage wait time: " << totalWaitTime / completedProcesses
                 << "\nAverage turn around time: " << totalTurnAroundTime / completedProcesses
                 << "\nAverage response time: " << (totalResponseTime / 1000) / completedProcesses << endl;    

    PrioSolution.close();
}