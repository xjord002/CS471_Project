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
        process.responseTime = 0.0;
        // Add data to the end of the queue as they are read in.
        prioProcesses.push_back(process);

        counter++;

        if(counter >= 500) {
            break;
        }
    }
    inputFile.close();
}

struct ComparePrio {
    bool operator()(prioProcess& a, prioProcess& b) {

        return a.prio > b.prio;
    }
};

void PRIO(vector<prioProcess> &processes) {
    int n = processes.size();
    double finishTime = 0.0;
    double completedProcesses = 0.0;
    double totalWaitTime = 0.0;
    double turnAroundTime = 0.0;
    double totalTurnAroundTime = 0.0;
    double totalBurstTime = 0.0;
    double totalResponseTime = 0.0;
    ofstream PrioSolution;
    PrioSolution.open("Output-PriorityScheduling.txt");
    priority_queue<prioProcess, vector<prioProcess>, ComparePrio> readyQueue;

    cout << "Arrival Time" << setw(16) << "Burst Length" << setw(15) << "Priority"
         << setw(17) << "Finish Time" << setw(20) << "Turn Around Time" << setw(13) 
         << "Wait Time" << endl;

    for(prioProcess& process : processes) {
        if(process.arrivalTime > finishTime) {
            finishTime = process.arrivalTime;
        }
        if(process.responseTime == 0) {
            process.responseTime = process.waitTime - process.arrivalTime;
        }

        process.waitTime = finishTime - process.arrivalTime;
        finishTime += process.burstLength;
        turnAroundTime = finishTime - process.arrivalTime;
        totalWaitTime += process.waitTime;
        totalTurnAroundTime += turnAroundTime;
        totalBurstTime += process.burstLength;
        completedProcesses++;
        cout << setw(5) << process.arrivalTime << setw(17) << process.burstLength << setw(17) 
                << process.prio << setw(17) << finishTime << setw(17) << turnAroundTime
                << setw(16) << process.waitTime << setw(17) << process.responseTime << endl;
    }
    cout << "Completed Processes: " << completedProcesses << endl;
    cout << "Total elapsed time: " << finishTime << endl;
    cout << "Throughput: " << completedProcesses / finishTime << endl;
    cout << "CPU Utilization: " << totalBurstTime / finishTime << endl;
    cout << "Average wait time: " << totalWaitTime / completedProcesses << endl;
    cout << "Average Turn Around Time: " << totalTurnAroundTime / completedProcesses << endl;
    cout << "Average Response Time: " << endl;    

    PrioSolution.close();
}