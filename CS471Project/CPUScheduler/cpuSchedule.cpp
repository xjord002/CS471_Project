#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int main() {
    ifstream fin("Datafile1.txt");
    if(!fin) {
        cerr << "Failed to open the text file." << endl;
        return 1;
    }

    string header;
    getline(fin, header);

    int n = 513;
    vector<int> arriveTime, burstLength, prio;
    int a, b, p;
    while(fin >> a >> b >> p) {
        arriveTime.push_back(a);
        burstLength.push_back(b);
        prio.push_back(p);
    }

    for(size_t i = 0; i < n; i++) {
        cout << "Arrival Time: " << setw(5) << arriveTime[i] << "  Burst Length: " << setw(3) << burstLength[i] << "  Priority: " << prio[i] << endl;
    }

    fin.close();

    return 0;
}