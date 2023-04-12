#include "session.h"
#include "hrvgraph.h"
#include "data.h"
#include <iostream>
#include <vector>

using namespace std;

Session::Session(QCustomPlot *customPlot, int coherenceType, QObject *parent)
    : QObject{parent},
      graph{new HRVGraph(customPlot)},
      interval{1},
      data{new Data()},
      coherenceType{coherenceType}
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
    int hr = data->getHeartRate(coherenceType, curTime);
    if (hr == -1) return;
    graph->addHeartRate(curTime, hr);
}

int Session::getTime(){
    return curTime;
}

QTimer* Session::getTimer(){
    return timer;
}
