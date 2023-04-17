#include "Record.h"

Record::Record(
    const double averageCoherence,
    const QDateTime& startTime,
    const int duration,
    const double achievementScore,
    const vector<double> percentCoh
)
    : percentCoh{percentCoh}
{
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
            + "   Duration: " + QString::number(duration/60) + ((duration%60 < 10) ? + ":0" + QString::number(duration%60) : + ":" + QString::number(duration%60)) + "\n"
            + "   Time Spent in High Coherence: " + QString::number(percentCoh[0] * 100.0) + "%\n"
            + "   Time Spent in Medium Coherence: " + QString::number(percentCoh[1] * 100.0) + "%\n"
            + "   Time Spent in Low Coherence: " + QString::number(percentCoh[2] * 100.0) + "%\n";

    return newString;
}


// getters
double Record::getAvgCoherence() { return averageCoherence; }
QDateTime Record::getStartTime() { return startTime; }
int Record::getAchievementScore() { return achievementScore; }
int Record::getDuration() { return duration; }


// setters
void Record::setDuration(int d) { duration = d; }
