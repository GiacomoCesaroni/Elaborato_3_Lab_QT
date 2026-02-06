#ifndef ACTIVITYTRACKER_H
#define ACTIVITYTRACKER_H

#include "Activity.h"
#include <map>
#include <list>
#include <QDate>

class ActivityTracker {
private:
    std::map<QDate, std::list<Activity>> activities;

public:
    ActivityTracker();

    void addActivity(QDate date, Activity activity);
    void removeActivity(QDate date, const Activity &activity);
    std::list<Activity> getActivitiesForDate(const QDate& date) const;
    std::map<QDate, std::list<Activity>> getAllActivities() const;
    bool hasActivitiesForDate(const QDate& date) const;
};

#endif //ACTIVITYTRACKER_H
