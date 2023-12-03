#include "sjf.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
 
using namespace std;

/*
 * A function to compare arrial times of each process
 * and returns true if arrial time a is less than (before)
 * arriavl time b.
*/
bool compareArrivalTime(sjfProcess& a, sjfProcess& b) {
    if(a.arrivalTime == b.arrivalTime) {
        return a.burstLength < b.burstLength;
    }
    return a.arrivalTime < b.arrivalTime;
}

/* 
 * Function to read in the Datafile1.txt file
*/
void readFile(const string &fin, vector<sjfProcess> &sjfProcesses) {
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

    sjfProcess process;
    int counter = 0;
    // While inputFile, the first column is arrival time, 
    // second column is burst length, and the last column is priority.
    while(inputFile >> process.arrivalTime >> process.burstLength >> process.prio) {
        process.waitTime = 0.0;
        process.responseTime = -1;
        process.remainingBurstLength = process.burstLength;
        // Add data to the end of the queue as they are read in.
        sjfProcesses.push_back(process);
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
 * The function to handle shortest job first.
*/
void SJF(vector<sjfProcess> &sjfProcesses) {
    int n = sjfProcesses.size();
    double totalElapsedTime = 0.0;
    double completedProcesses = 0.0;
    double totalWaitTime = 0.0;
    double turnAroundTime = 0.0;
    double totalTurnAroundTime = 0.0;
    double totalBurstTime = 0.0;
    double totalResponseTime = 0.0;
    int index = 0;

    // Opening the output file for the solutions
    ofstream SJFSolution;
    SJFSolution.open("Output-SJFScheduling.txt");
    sort(sjfProcesses.begin(), sjfProcesses.end(), compareArrivalTime);

    for(int i = 0; i < n; i++) {
        if(i > 0 && sjfProcesses[i].arrivalTime == sjfProcesses[i - 1].arrivalTime && sjfProcesses[i].burstLength < sjfProcesses[i - 1].burstLength) {
            swap(sjfProcesses[i], sjfProcesses[i - 1]);
        }

        if(sjfProcesses[i].arrivalTime > totalElapsedTime) {
            totalElapsedTime = sjfProcesses[i].arrivalTime;
        }
        if(sjfProcesses[i].responseTime == -1.0) {
            sjfProcesses[i].responseTime = totalElapsedTime;
        }

        sjfProcesses[i].waitTime = max(0.0, totalElapsedTime - sjfProcesses[i].arrivalTime);
        totalWaitTime += sjfProcesses[i].waitTime;
        totalElapsedTime += sjfProcesses[i].burstLength;
        turnAroundTime = totalElapsedTime - sjfProcesses[i].arrivalTime;
        totalTurnAroundTime += turnAroundTime;
        totalBurstTime += sjfProcesses[i].burstLength;

        totalResponseTime += sjfProcesses[i].responseTime;
        completedProcesses++;
    }

    // Outputting all the solutions into the output file
    SJFSolution << "Completed processes: " << completedProcesses
                << "\nTotal elapsed time: " << totalElapsedTime / 1000
                << "\nThroughput: " << completedProcesses / (totalElapsedTime / 1000)
                << "\nCPU Utilization: " << totalBurstTime / totalElapsedTime
                << "\nAverage wait time: " << totalWaitTime / completedProcesses
                << "\nAverage turn around time: " << totalTurnAroundTime / completedProcesses
                << "\nAverage response time: " << (totalResponseTime / 1000) / completedProcesses << endl;
    
    SJFSolution.close();
}