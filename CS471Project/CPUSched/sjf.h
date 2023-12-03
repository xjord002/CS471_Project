#ifndef SJF_H
#define SJF_H

#include <vector>
#include <string>

struct sjfProcess {
    double arrivalTime;
    double burstLength;
    int prio;
    double waitTime;
    double responseTime;
    double remainingBurstLength;
};

void readFile(const std::string &fin, std::vector<sjfProcess> &sjfProcesses);
void SJF(std::vector<sjfProcess> &sjfProcesses);

#endif // SJF_H