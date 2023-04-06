#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDateTime>
#include <QTime>



class Record {

public:
    Record(const QString& treatment, const QDateTime& startTime, const int powerLevel, const int duration);
    void setPowerLevel(int p);
    void setDuration(int durationMS);

    QString toString();
    QString getTreatment();
    QDateTime getStartTime();
    int getPowerLevel();
    int getDuration(); //Seconds

private:
    QString treatment;
    QDateTime startTime;
    int powerLevel;
    int duration;

};

#endif // RECORD_H
