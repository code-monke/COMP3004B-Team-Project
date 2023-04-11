#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "qcustomplot.h"

class HRVGraph;

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QCustomPlot *customPlot,  QObject *parent = nullptr);
    void start();
    void stop();

private:
    HRVGraph *graph;

    QTimer* timer;
    int curTime;
    int interval;

    void updateGraph();


signals:

};

#endif // SESSION_H
