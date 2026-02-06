#include "ActivityTracker.h"

ActivityTracker::ActivityTracker() {}

void ActivityTracker::addActivity(QDate date, Activity activity) {
    activities[date].push_back(activity);
}

void ActivityTracker::removeActivity(QDate date, const Activity &activity) {
    auto it = activities.find(date);
    if (it != activities.end()) {
        it->second.remove(activity);
        if (it->second.empty()) {
            activities.erase(it);
        }
    }
}

std::list<Activity> ActivityTracker::getActivitiesForDate(const QDate& date) const {
    auto it = activities.find(date);
    if (it != activities.end()) {
        return it->second;
    }
    return std::list<Activity>();
}