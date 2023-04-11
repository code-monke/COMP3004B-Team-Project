#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDateTime>
#include <QTime>



class Record {

public:
    Record(const double averageCoherence, const QDateTime& startTime, const int duration, const int achievementScore);
    void setDuration(int durationMS);

    QString toString();
    double getAvgCoherence();
    QDateTime getStartTime();
    int getAchievementScore();
    int getDuration(); //Seconds

private:
    double averageCoherence;
    QDateTime startTime;
    int achievementScore;
    int duration;

};

#endif // RECORD_H
