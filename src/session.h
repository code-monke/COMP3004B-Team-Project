#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "qcustomplot.h"

class HRVGraph;
class Data;

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QCustomPlot *customPlot, int coherenceType,  QObject *parent = nullptr);
    void start();
    void stop();

    QTimer* getTimer();
    int getTime();

private:
    HRVGraph *graph;
    Data *data;

    QTimer* timer;
    int curTime;
    int interval;
    int coherenceType;

    void update();


signals:

};

#endif // SESSION_H
