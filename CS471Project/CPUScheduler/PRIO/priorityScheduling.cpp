#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
 
using namespace std;

struct Process {
    double arrivalTime;
    double burstLength;
    int prio;
    double waitTime;
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
        process.waitTime = 0.0;
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
    if(a.arrivalTime == b.arrivalTime) {
        return a.prio > b.prio;
    }
    return a.arrivalTime < b.arrivalTime;
}

void PRIO(vector<Process> &processes) {
    int n = processes.size();
    double finishTime = 0.0;
    double totalElapsedTime = 0.0;
    double completedProcesses = 0.0;
    double totalWaitTime = 0.0;
    double turnAroundTime = 0.0;
    double totalTurnAroundTime = 0.0;
    double cumulativeWaitTime = 0.0;
    double prevBurst = 0.0;
    sort(processes.begin(), processes.end(), comparePrio);

    cout << "Arrival Time" << setw(16) << "Burst Length" << setw(15) << "Finish Time" 
         << setw(20) << "Turn Around Time" << setw(13) << "Wait Time" << endl;
    for(Process& process : processes) {
        if(process.arrivalTime > finishTime) {
            finishTime = process.arrivalTime;
        }
        process.waitTime = finishTime - process.arrivalTime;
        finishTime += process.burstLength;
        turnAroundTime = finishTime - process.arrivalTime;
        totalWaitTime += process.waitTime;
        cout << setw(5) << process.arrivalTime << setw(17) << process.burstLength << setw(17) 
             << finishTime << setw(17) << turnAroundTime
             << setw(16) << process.waitTime << endl;
    }
}
 
int main() {
    vector<Process> processes;
    readFile("..\\Datafile1.txt", processes);
    PRIO(processes);
 
    return 0;
}