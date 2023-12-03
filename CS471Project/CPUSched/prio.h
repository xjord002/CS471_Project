#ifndef PRIO_H
#define PRIO_H

#include <vector>
#include <string>

struct prioProcess {
    double arrivalTime;
    double burstLength;
    int prio;
    double waitTime;
    double responseTime;
};

void readFile(const std::string &fin, std::vector<prioProcess> &prioProcesses);
void PRIO(std::vector<prioProcess> &prioProcesses);

#endif // PRIO_H