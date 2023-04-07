#include "session.h"
#include "hrvgraph.h"
#include <iostream>
using namespace std;

Session::Session(QCustomPlot *customPlot, QObject *parent)
    : QObject{parent},
      graph{new HRVGraph(customPlot)},
      interval{1}
{

}

void Session::start(){
    curTime = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Session::updateGraph);
    timer->start(interval * 1000);
}

void Session::updateGraph(){
    curTime += interval;
    graph->addHeartRate(curTime, 1 + rand() % 10);
}
