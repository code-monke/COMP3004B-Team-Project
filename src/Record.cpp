#include "record.h"

Record::Record(const double averageCoherence, const QDateTime& startTime, const int duration, const int achievementScore) {

    if (startTime.isValid()) {
        this->averageCoherence = averageCoherence;
        this->startTime = startTime;
        this->achievementScore = achievementScore;
        this->duration = duration;
    }
}


QString Record::toString() {
    QString newString =
            startTime.toString("ddd h:mm ap") + "\n"
        + "   Average Coherence: " + QString::number(averageCoherence) + "\n"
            + "   Achivement Score: " + QString::number(achievementScore) + "\n"
            + "   Duration: " + QString::number(duration/60) + ((duration%60 < 10) ? + ":0" + QString::number(duration%60) : + ":" + QString::number(duration%60));

    return newString;
}


// getters
double Record::getAvgCoherence() { return averageCoherence; }
QDateTime Record::getStartTime() { return startTime; }
int Record::getAchievementScore() { return achievementScore; }
int Record::getDuration() { return duration; }


// setters
void Record::setDuration(int d) { duration = d; }
