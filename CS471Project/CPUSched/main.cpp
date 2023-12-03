#include "fifo.h"
#include "sjf.h"
#include "prio.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    // Queue for FIFO scheduling
    queue<fifoProcess> fifoProcesses;
    // Vector for SJF scheudling
    vector<sjfProcess> sjfProcesses;
    // Vector for Priority scheduling
    vector<prioProcess> prioProcesses;
    // Read in file for FIFO scheduling
    readFile("Datafile1.txt", fifoProcesses);
    // Read in file for SJF scheduling
    readFile("Datafile1.txt", sjfProcesses);
    // Read in file for Priority scheduling
    readFile("Datafile1.txt", prioProcesses);
    // Run the FIFO function
    FIFO(fifoProcesses);
    // Run the SJF function
    SJF(sjfProcesses);
    // Run the Priority function
    PRIO(prioProcesses);

    return 0;
}