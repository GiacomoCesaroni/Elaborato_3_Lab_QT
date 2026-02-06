#include "Activity.h"

Activity::Activity(const QString &activityName, const QString &description,
                   QTime timeStart, QTime timeEnd) {
    this->activityName = activityName;
    this->description = description;
    this->timeStart = timeStart;
    this->timeEnd = timeEnd;
}