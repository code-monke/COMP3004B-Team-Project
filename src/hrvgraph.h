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

    void addHeartRate(double curTime, double heartRate);
    void clear();

private:
    QCustomPlot *customPlot;
    QVector<double> x;
    QVector<double> y;

signals:

};

#endif // HRVGRAPH_H
