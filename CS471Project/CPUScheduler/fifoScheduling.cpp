#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

struct Process {
    int arrivalTime;
    int burstLength;
    int prio;
    int waitTime;
};

void readFile(const string &fin, queue<Process> &processes) {
    ifstream inputFile(fin);
    if(!inputFile.is_open()) {
        cerr << "File cannot be opened: " << fin << endl;

        return;
    }

    string header;
    getline(inputFile, header);

    Process process;
    while(inputFile >> process.arrivalTime >> process.burstLength >> process.prio) {
        process.waitTime = 0;
        processes.push(process);
    }

    inputFile.close();
}

void FIFO(queue<Process> &processes) {
    // cout << "Arrival Time " << " Burst Length " << " Wait Times" << endl;
    int currentTime = 0;
    int totalElapsedTime = 0;
    int completedProcesses = 0;
    int totalWaitTime = 0;
    int turnAroundTime = 0;
    int totalTurnAroundTime = 0;
    ofstream CompletedProcesses, TotalElapsedTime, Throughput, AverageWaitTime, AverageTurnAroundTime, AverageResponseTime;
    CompletedProcesses.open("CompletedProcesses.txt");
    TotalElapsedTime.open("TotalElapsedTime.txt");
    Throughput.open("Throughput.txt");
    AverageWaitTime.open("AverageWaitTime.txt");
    AverageTurnAroundTime.open("AverageTurnAroundTime.txt");

    while(!processes.empty()) {
        Process process = processes.front();
        processes.pop();

        process.waitTime = max(0, currentTime - process.arrivalTime);
        currentTime = max(currentTime, process.arrivalTime) + process.burstLength;
        totalElapsedTime = max(totalElapsedTime, currentTime);
        completedProcesses++;
        totalWaitTime += process.waitTime;
        turnAroundTime = process.burstLength + process.waitTime;
        totalTurnAroundTime += turnAroundTime;

        // cout << setw(10) << process.arrivalTime << setw(13) << process.burstLength
        //      << setw(13) << process.waitTime << endl;
    }
    CompletedProcesses << "Completed processes: " << completedProcesses;
    TotalElapsedTime << "Total elapsed time: " << totalElapsedTime / 1000 << " seconds.";
    Throughput << "Throughput: " << completedProcesses / (totalElapsedTime / 1000);
    AverageWaitTime << "Average wait time: " << totalWaitTime / completedProcesses;
    AverageTurnAroundTime << "Average turn around time: " << totalTurnAroundTime / completedProcesses;
}

int main() {
    queue<Process> processes;
    readFile("Datafile1.txt", processes);
    FIFO(processes);

    return 0;
}