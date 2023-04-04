#include "hrvgraph.h"
#include <iostream>

HRVGraph::HRVGraph(QCustomPlot* customPlot, QObject *parent)
    : QObject{parent},
      customPlot{customPlot},
      x{QVector<double>()},
      y{QVector<double>()}
{
    interval = 1000; //ms

    // Create graph
    customPlot->addGraph();

    // Give the axes some labels:
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Heart Rate");


    // Set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 60); // to change
    customPlot->yAxis->setRange(0, 11); // to change

    customPlot->replot();

    // Update Graph Every second
    curTime = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HRVGraph::updatePlot);
    timer->start(interval);

}

double HRVGraph::getRandomHeartRate(){
    int r = 1 + rand() % 10;
    return r;
}

/*
 * Adds a random heart rate to the HRV Graph at a set interval and
 * updates the graph
*/
void HRVGraph::updatePlot(){
    curTime += interval;

    double heartRate = getRandomHeartRate();
    x.push_back(curTime / 1000);
    y.push_back(heartRate);
    customPlot->graph(0)->setData(x, y);
    cout << "called: " << curTime / 1000 << " || " << heartRate << endl;

    //Redraw plot

    customPlot->replot();
}


