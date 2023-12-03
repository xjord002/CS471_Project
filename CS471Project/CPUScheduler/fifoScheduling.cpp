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
        // Add data to the end of the queue as they are read in.
        fifoProcesses.push(process);

        counter++;

        if(counter >= 500) {
            break;
        }
    }

    inputFile.close();
}

void FIFO(queue<fifoProcess> &fifoProcesses) {
    // cout << "Arrival Time " << " Burst Length " << " Wait Times" << endl;
    double currentTime = 0.0;
    double totalElapsedTime = 0.0;
    double completedProcesses = 0.0;
    double totalWaitTime = 0.0;
    double turnAroundTime = 0.0;
    double totalTurnAroundTime = 0.0;
    // Opening the output file for each solution
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
    FIFOSolution << "Completed processes: " << completedProcesses
                 << "\nTotal elapsed time: " << totalElapsedTime / 1000
                 << "\nThroughput: " << completedProcesses / (totalElapsedTime / 1000)
                 << "\nAverage wait time: " << totalWaitTime / completedProcesses
                 << "\nAverage turn around time: " << totalTurnAroundTime / completedProcesses;
}