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
    void finish();

    QTimer* getTimer();
    int getTime();

signals:
    void sessionFinished(Record *record);
    void sessionUpdated(double achieveScore, double cohScore, int curCohLvl, int curtime);


private:
    HRVGraph *graph;
    Data *data;
    QTimer* timer;
    Record *record;
    QDateTime startTime;

    int curTime;
    int interval;
    //Stats
    double achieveScore;
    double last64cohSum;
    double percentCoh[3]; // % time spent in {high, medium, low} coh level

    void update();
    int cohScoreToLvl(double cohScore);


signals:

};

#endif // SESSION_H
