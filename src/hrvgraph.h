#ifndef HRVGRAPH_H
#define HRVGRAPH_H

#include <QObject>
#include "qcustomplot.h"

using namespace std;

class HRVGraph : public QObject
{
    Q_OBJECT
public:
    explicit HRVGraph(QCustomPlot *customPlot, QObject *parent=nullptr);


private:
    QCustomPlot *customPlot;
    QVector<double> x;
    QVector<double> y;
    int curTime;
    int interval;

    double getRandomHeartRate();
    void updatePlot();


signals:

};

#endif // HRVGRAPH_H
