#include "session.h"
#include "hrvgraph.h"
#include "data.h"
#include "Record.h"
#include "constants.h"
#include <iostream>
#include <vector>

using namespace std;

Session::Session(QCustomPlot *customPlot, int cohLvl, QObject *parent)
    : QObject{parent},
      graph{new HRVGraph(customPlot)},
      data{new Data(cohLvl)},
      record{NULL},
      interval{1},
      coherenceType{cohLvl},
      achieveScore{0},
      last64cohSum{0}
{

}

void Session::start(){
    curTime = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Session::update);
    timer->start(interval * 1000);
}

void Session::stop(){
    timer->stop();
    graph->clear();
}

void Session::update(){
    curTime += interval;

    //Read heart rate and update graph
    double heartRate = data->getHeartRate(curTime);
    if (heartRate != -1) graph->addHeartRate(curTime, heartRate);

    //Read coherence score every 5 seoncds
    double cohScore = -1;
    if (curTime % 5 == 0){
        cohScore = data->getCoherence(curTime);
        achieveScore += cohScore;
        last64cohSum += cohScore;
    }

    //Read coherence level every 64 seconds
    int curCohLvl = -1;
    if (curTime % 64 == 0){
        // Determine current Coherence Level by averaging out the coherence scores over
        // the last 64 seconds
        // The thresholds for low, medium and high levels of coherence are determined as
        // if the challenge level was 3
        double cohAvg = achieveScore / (64 / 5);
        if (cohAvg < 1.8) curCohLvl = LOW_COH;
        else if (cohAvg > 4.0) curCohLvl  = HIGH_COH;
        else curCohLvl = MED_COH;
        last64cohSum = 0;
        cout << curCohLvl << endl;
    }

    emit sessionUpdated(achieveScore, cohScore, curCohLvl, curTime);
}

int Session::getTime(){
    return curTime;
}

QTimer* Session::getTimer(){
    return timer;
}
