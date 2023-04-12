
#ifndef DATA_H
#define DATA_H

#include <vector>;

using namespace std;

class Data
{
public:
    Data();
public:
    double getHeartRate(int coherenceType, int t);
    double getCoherence(int coherenceType, int t);
private:
    // Data -> {heart_rates, coherence_scores}
    vector<vector<double>> hcData; // high coherence data
    vector<vector<double>> mcData; // med coherence data
    vector<vector<double>> lcData; // low coherence data
};

#endif // DATA_H
