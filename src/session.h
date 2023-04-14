#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "qcustomplot.h"

class HRVGraph;
class Data;
class Record;

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QCustomPlot *customPlot, int cohLvL,  QObject *parent = nullptr);
    void start();
    void stop();

    QTimer* getTimer();
    int getTime();

signals:
    void sessionFinished();
    void sessionUpdated(double achieveScore, double cohScore, int curCohLvl, int curtime);


private:
    HRVGraph *graph;
    Data *data;
    QTimer* timer;
    Record *record;
    int curTime;
    int interval;
    int coherenceType;
    double achieveScore;
    double last64cohSum;

    void update();


signals:

};

#endif // SESSION_H
