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
        // Add data to the end of the queue as they are read in.
        sjfProcesses.push_back(process);

        counter++;

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
    double finishTime = 0.0;
    double totalElapsedTime = 0.0;
    double completedProcesses = 0.0;
    double totalWaitTime = 0.0;
    double totalTurnAroundTime = 0.0;
    double totalBurstTime = 0.0;

    // Opening the output file for the solutions
    ofstream SJFSolution;
    SJFSolution.open("Output-SJFScheduling.txt");
    sort(sjfProcesses.begin(), sjfProcesses.end(), compareArrivalTime);

    // cout << "Arrival Time" << setw(15) << "Burst Length" << setw(15) << "Finish Time" << setw(20) << "Turn Around Time" << setw(20) << "Wait Time" << endl;
    for(sjfProcess& process : sjfProcesses) {
        if(process.arrivalTime > finishTime) {
            finishTime = process.arrivalTime;
        }
        process.waitTime = max(0.0, finishTime - process.arrivalTime);
        totalWaitTime += process.waitTime;
        finishTime += process.burstLength;
        double turnAroundTime = finishTime - process.arrivalTime;
        totalTurnAroundTime += turnAroundTime;
        totalElapsedTime = max(totalElapsedTime, finishTime);
        totalBurstTime += process.burstLength;
        // cout << setw(8) << process.arrivalTime << setw(12) << process.burstLength << setw(17) << finishTime << setw(19) << turnAroundTime << setw(20) << process.waitTime << endl;
        completedProcesses++;
    }
    
    // Outputting each solution to the solution file
    SJFSolution << "Completed processes: " << completedProcesses
                << "\nTotal elapsed time: " << totalElapsedTime / 1000
                << "\nThroughput: " << completedProcesses / (totalElapsedTime / 1000)
                << "\nCPU Utilization: " << totalBurstTime / finishTime
                << "\nAverage wait time: " << totalWaitTime / completedProcesses
                << "\nAverage turn around time: " << totalTurnAroundTime / completedProcesses
                << "\nAverage response time: " << endl;
    
    SJFSolution.close();
}