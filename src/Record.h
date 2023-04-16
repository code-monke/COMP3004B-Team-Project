#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDateTime>
#include <QTime>
#include <vector>

using namespace std;

class Record {

public:
    Record(
        const double averageCoherence,
        const QDateTime& startTime,
        const int duration,
        const double achievementScore,
        const vector<double> percentCoh
    );
    const vector<double> percentCoh;
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
