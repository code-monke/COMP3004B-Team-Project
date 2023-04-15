
#ifndef DATA_H
#define DATA_H

#include <vector>

using namespace std;

class Data
{
public:
    Data(int cohLvl);
public:
    double getHeartRate(int t);
    double getCoherence(int t);
private:
    // Data -> {heart_rates, coherence_scores}
    vector<vector<double>> hcData; // high coherence data
    vector<vector<double>> mcData; // med coherence data
    vector<vector<double>> lcData; // low coherence data
    // pointer to data currently being used (hc,mc, lc)
    vector<vector<double>> *activeData;
};

#endif // DATA_H
