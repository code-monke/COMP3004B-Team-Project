#include "hrvgraph.h"
#include <iostream>

HRVGraph::HRVGraph(QCustomPlot* customPlot, QObject *parent)
    :   QObject{parent},
        customPlot{customPlot},
        x{QVector<double>()},
        y{QVector<double>()}
{
    // Create graph
    customPlot->addGraph();

    // Give the axes some labels:
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Heart Rate");

    // Set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 210); // to change
    customPlot->yAxis->setRange(45, 115); // to change

    customPlot->replot();

}

//adding heart rate to plot
void HRVGraph::addHeartRate(double t, double heartRate){
    x.push_back(t);
    y.push_back(heartRate);
    customPlot->graph(0)->setData(x, y);
    customPlot->replot();
}

//clearing graph
void HRVGraph::clear(){
    customPlot->clearGraphs();
}

