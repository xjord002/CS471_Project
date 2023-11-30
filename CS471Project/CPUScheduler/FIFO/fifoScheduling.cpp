#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

// A struct with characteristics of a Process
struct Process {
    int arrivalTime;
    int burstLength;
    int prio;
    int waitTime;
};

// Function to read in the Datafile1.txt file
void readFile(const string &fin, queue<Process> &processes) {
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
    // Opening the output file for each solution
    ofstream CompletedProcesses, TotalElapsedTime, Throughput, AverageWaitTime, AverageTurnAroundTime, AverageResponseTime;
    CompletedProcesses.open("CompletedProcesses.txt");
    TotalElapsedTime.open("TotalElapsedTime.txt");
    Throughput.open("Throughput.txt");
    AverageWaitTime.open("AverageWaitTime.txt");
    AverageTurnAroundTime.open("AverageTurnAroundTime.txt");

    while(!processes.empty()) {
        // Point to the first element of the queue
        Process process = processes.front();
        // Remove the element
        processes.pop();

        // Wait time for each process
        process.waitTime = max(0, currentTime - process.arrivalTime);
        currentTime = max(currentTime, process.arrivalTime) + process.burstLength;
        totalElapsedTime = max(totalElapsedTime, currentTime);
        completedProcesses++;

        // Calculating the total wait time
        totalWaitTime += process.waitTime;
        // Calculating the turn around time
        turnAroundTime = process.burstLength + process.waitTime;
        // Calculating the total turn around time
        totalTurnAroundTime += turnAroundTime;

        // cout << setw(10) << process.arrivalTime << setw(13) << process.burstLength
        //      << setw(13) << process.waitTime << endl;
    }
    // Outputting each solution to its own text file
    CompletedProcesses << "Completed processes: " << completedProcesses;
    TotalElapsedTime << "Total elapsed time: " << totalElapsedTime / 1000 << " seconds.";
    Throughput << "Throughput: " << completedProcesses / (totalElapsedTime / 1000);
    AverageWaitTime << "Average wait time: " << totalWaitTime / completedProcesses;
    AverageTurnAroundTime << "Average turn around time: " << totalTurnAroundTime / completedProcesses;
}

int main() {
    queue<Process> processes;
    // Calling the file reading function
    readFile("../Datafile1.txt", processes);
    // Calling the First In First Out function
    FIFO(processes);

    return 0;
}