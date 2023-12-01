#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
 
using namespace std;

struct Process {
    int arrivalTime;
    int burstLength;
    int prio;
    int waitTime;
};

// Function to read in the Datafile1.txt file
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
    int counter = 0;
    // While inputFile, the first column is arrival time, 
    // second column is burst length, and the last column is priority.
    while(inputFile >> process.arrivalTime >> process.burstLength >> process.prio) {
        // wait time is equal to 0
        process.waitTime = 0;
        // Add data to the end of the queue as they are read in.
        processes.push_back(process);

        counter++;

        if(counter >= 500) {
            break;
        }
    }
    inputFile.close();
}

bool comparePrio(Process& a, Process& b) {
    return a.prio > b.prio;
}

bool compareBurstLength(Process& a, Process& b) {
    return a.burstLength < b.burstLength;
}

void PRIO(vector<Process> &processes) {
    int n = processes.size();
    int finishTime = 0;
    int totalElapsedTime = 0;
    int completedProcesses = 0;
    int totalWaitTime = 0;
    int turnAroundTime = 0;
    int totalTurnAroundTime = 0;
    sort(processes.begin(), processes.end(), comparePrio);
}
 
int main() {
    vector<Process> processes;
    readFile("..\\Datafile1.txt", processes);
 
    return 0;
}