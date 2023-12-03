#ifndef FIFO_H
#define FIFO_H

#include <queue>
#include <string>

struct fifoProcess {
    double arrivalTime;
    double burstLength;
    int prio;
    double waitTime;
    double responseTime;
};

void readFile(const std::string &fin, std::queue<fifoProcess> &fifoProcesses);
void FIFO(std::queue<fifoProcess> &fifoProcesses);

#endif // FIFO_H