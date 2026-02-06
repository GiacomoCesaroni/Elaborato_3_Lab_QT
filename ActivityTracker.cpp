#include "ActivityTracker.h"

ActivityTracker::ActivityTracker() {}

void ActivityTracker::addActivity(QDate date, Activity activity) {
    activities[date].push_back(activity);
}