#include "Activity.h"

Activity::Activity(const QString &activityName, const QString &description,
                   QTime timeStart, QTime timeEnd) {
    this->activityName = activityName;
    this->description = description;
    this->timeStart = timeStart;
    this->timeEnd = timeEnd;
}

QTime Activity::getTimeStart() const {
    return this->timeStart;
}

QTime Activity::getTimeEnd() const {
    return this->timeEnd;
}

QString Activity::getActivityName() const {
    return this->activityName;
}

QString Activity::getDescription() const {
    return this->description;
}
