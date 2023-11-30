#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
 
using namespace std;

/*
 * A struct with characteristics of a Process
*/
struct Process {
    int arrivalTime;
    int burstLength;
    int prio;
    int waitTime;
};

/* 
 * Function to read in the Datafile1.txt file
*/
void readFile(const string &fin, vector<Process> &processes) {
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

    Process process;
    // While inputFile, the first column is arrival time, 
    // second column is burst length, and the last column is priority.
    while(inputFile >> process.arrivalTime >> process.burstLength >> process.prio) {
        // wait time is equal to 0
        process.waitTime = 0;
        // Add data to the end of the queue as they are read in.
        processes.push_back(process);
    }

    inputFile.close();
}

bool compareArrivalTime(Process& a, Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

/*
 * A function to compare burst lengths of each process
 * and returns true if burst length a is less than
 * burst length b.
*/
bool compareBurstLength(Process& a, Process& b) {
    return a.burstLength < b.burstLength;
}

/*
 * The function to handle shortest job first.
*/
void SJF(vector<Process> &processes) {
    int n = processes.size();
    int currentTime = 0;
    int totalElapsedTime = 0;
    int completedProcesses = 0;
    int totalWaitTime = 0;
    int turnAroundTime = 0;
    int totalTurnAroundTime = 0;
    // Opening the output file for each solution
    // ofstream CompletedProcesses, TotalElapsedTime, Throughput, AverageWaitTime, AverageTurnAroundTime, AverageResponseTime;
    // CompletedProcesses.open("CompletedProcesses.txt");
    // TotalElapsedTime.open("TotalElapsedTime.txt");
    // Throughput.open("Throughput.txt");
    // AverageWaitTime.open("AverageWaitTime.txt");
    // AverageTurnAroundTime.open("AverageTurnAroundTime.txt");
    sort(processes.begin(), processes.end(), compareArrivalTime);

    cout << "Current Time" << setw(15) << "Burst Length" << endl;
    for(Process& process : processes) {
        sort(processes.begin(), processes.end(), compareBurstLength);
        if(process.arrivalTime > currentTime) {
            currentTime = process.arrivalTime;
        }

        //cout << "Process time: " << currentTime << " to " << currentTime + process.burstLength << endl;
        currentTime += process.burstLength;

        process.waitTime = max(0, currentTime - process.arrivalTime);
        totalElapsedTime = max(totalElapsedTime, currentTime);
        completedProcesses++;
        cout << setw(10) << currentTime << setw(13) << process.burstLength << endl;

        // Calculating the total wait time
        totalWaitTime += process.waitTime;
        // Calculating the turn around time
        turnAroundTime = process.burstLength + process.waitTime;
        // Calculating the total turn around time
        totalTurnAroundTime += turnAroundTime;
    }
    
    // Outputting each solution to its own text file
    // CompletedProcesses << "Completed processes: " << completedProcesses;
    // CompletedProcesses << "Completed processes: " << completedProcesses;
    // TotalElapsedTime << "Total elapsed time: " << totalElapsedTime / 1000 << " seconds.";
    // Throughput << "Throughput: " << completedProcesses / (totalElapsedTime / 1000);
    // AverageWaitTime << "Average wait time: " << totalWaitTime / completedProcesses;
    // AverageTurnAroundTime << "Average turn around time: " << totalTurnAroundTime / completedProcesses;
}
 
int main() {
    vector<Process> processes;
    readFile("../Datafile1.txt", processes);
    SJF(processes);
 
    return 0;
}