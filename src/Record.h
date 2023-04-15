#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDateTime>
#include <QTime>



class Record {

public:
    Record(
        const double averageCoherence,
        const QDateTime& startTime,
        const int duration,
        const double achievementScore,
        const double percentCoh[3]
    );
    const double percentCoh[3];
    void setDuration(int durationMS);

    QString toString();
    double getAvgCoherence();
    QDateTime getStartTime();
    int getAchievementScore();
    int getDuration(); //Seconds

private:
    double averageCoherence;
    QDateTime startTime;
    double achievementScore;
    int duration;

};

#endif // RECORD_H
