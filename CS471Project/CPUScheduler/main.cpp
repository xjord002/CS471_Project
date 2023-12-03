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
    queue<fifoProcess> fifoProcesses;
    vector<sjfProcess> sjfProcesses;
    vector<prioProcess> prioProcesses;
    readFile("Datafile1.txt", fifoProcesses);
    FIFO(fifoProcesses);
    SJF(sjfProcesses);
    PRIO(prioProcesses);

    return 0;
}