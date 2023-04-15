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
      achieveScore{0},
      last64cohSum{0},
      percentCoh{0, 0, 0} //{high, medium, low}
{

}

void Session::start(){
    curTime = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Session::update);
    timer->start(interval * 1000);
    startTime = QDateTime::currentDateTime();
}

void Session::update(){
    if (curTime == 200) {
        finish();
        return;
    }
    //Read heart rate and update graph
    double heartRate = data->getHeartRate(curTime);
    if (heartRate != -1) graph->addHeartRate(curTime, heartRate);

    //Read coherence every 5 seconds
    double cohScore = -1;
    if (curTime >= 5 && curTime % 5 == 0){
        cohScore = data->getCoherence(curTime);
        achieveScore += cohScore;
        last64cohSum += cohScore;

        //Update % time spent in each coherence level
        double cohLvl = cohScoreToLvl(cohScore);
        double *percent;
        if (cohLvl == HIGH_COH) percent = &percentCoh[0];
        else if (cohLvl == MED_COH) percent = &percentCoh[1];
        else if (cohLvl == LOW_COH) percent = &percentCoh[2];

        *percent = ((*percent * (curTime - 5)) + 5) / curTime;

    }

    //Read coherence level every 64 seconds
    int curCohLvl = -1;
    if (curTime >= 64 && curTime % 64 == 0){
        // Determine current Coherence Level by averaging out the coherence scores over
        // the last 64 seconds
        double cohAvg = last64cohSum / (64 / 5);
        curCohLvl = cohScoreToLvl(cohAvg);
        last64cohSum = 0;
    }

    emit sessionUpdated(achieveScore, cohScore, curCohLvl, curTime);
    curTime += interval;
}

/*
 * Compute stats for summary view
 * Create record and send signal
 */
void Session::finish(){
    //Average coherence
    double cohAvg = achieveScore / (curTime / 5.0);

    Record *record = new Record(
        cohAvg,
        startTime,
        (int) curTime,
        achieveScore,
        percentCoh
    );

    timer->stop();
    graph->clear();
    emit sessionFinished(record);
}

/*
 * Returns coherence level (high, medium, low) based on cohScore
 * The thresholds for low, medium and high levels of coherence are determined as
 * if the challenge level was 3
 */
int Session::cohScoreToLvl(double cohScore){
    if (cohScore < 1.8) return LOW_COH;
    else if (cohScore > 4.0) return HIGH_COH;
    return MED_COH;
}

int Session::getTime(){
    return curTime;
}

QTimer* Session::getTimer(){
    return timer;
}
