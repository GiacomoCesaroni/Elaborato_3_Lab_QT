#include <gtest/gtest.h>
#include "../../ActivityTracker.h"
#include "../../Activity.h"

#include <QDate>
#include <QTime>
#include <list>
#include <map>

class ActivityTrackerTest : public testing::Test {
protected:
    ActivityTracker* tracker;
    Activity* cane;
    Activity* palestra;
    Activity* studio;
    QDate date1, date2;

    void SetUp() {
        tracker = new ActivityTracker();
        cane = new Activity{"Cane", "Portare Fuori il cane", QTime(8, 0), QTime(9,30)};
        palestra = new Activity{"Palestra", "Andare in palestra", QTime(14, 0), QTime (16, 0)};
        studio = new Activity{"Studio", "Studiare programmazione", QTime(17, 0), QTime (21, 30)};

        date1 = QDate(2026, 1, 4);
        date2 = QDate(2026, 2, 12);
    }
    void TearDown() {
        delete tracker;
        delete cane;
        delete palestra;
        delete studio;
    }
};

TEST(ActivityTest, Constructor_setParameterCorrectly) {
    Activity activity{"Spesa", "Fare la spesa", QTime(13, 0), QTime(14, 30)};

    EXPECT_EQ(activity.getActivityName(), "Spesa");
    EXPECT_EQ(activity.getDescription(), "Fare la spesa");
    EXPECT_EQ(activity.getTimeStart(), QTime(13, 0));
    EXPECT_EQ(activity.getTimeEnd(), QTime(14, 30));
}

TEST(ActivityTest, EqualOperator_CompareAll) {
    Activity activity1{"Leggere", "Finire il libro", QTime(15, 0), QTime(17, 0)};
    Activity activity2{"Leggere", "Finire il libro", QTime(15, 0), QTime(17, 0)};

    EXPECT_TRUE(activity1 == activity2);

    Activity activity3{"Leggere", "Andare in palestra", QTime(15, 0), QTime(17, 0)};
    Activity activity4{"Palestra", "Finire il libro", QTime(15, 0), QTime(17, 0)};

    EXPECT_FALSE(activity1 == activity3);
    EXPECT_FALSE(activity1 == activity4);
}

TEST_F(ActivityTrackerTest, addActivity_correctlyAdded) {
    tracker->addActivity(date1, *cane);
    std::list<Activity> activities = tracker->getActivitiesForDate(date1);

    ASSERT_EQ(activities.size(), 1);

    EXPECT_EQ(activities.front().getActivityName(), "Cane");
    EXPECT_EQ(activities.front().getDescription(), "Portare Fuori il cane");
}

TEST_F(ActivityTrackerTest, addActivity_sameDateActivities_sorted) {
    tracker->addActivity(date1, *cane);
    tracker->addActivity(date1, *palestra);
    tracker->addActivity(date1, *studio);

    std::list<Activity> activities = tracker->getActivitiesForDate(date1);
    ASSERT_EQ(activities.size(), 3);

    std::vector<Activity> vec(activities.begin(), activities.end());

    EXPECT_EQ(vec[0].getActivityName(), "Cane");
    EXPECT_EQ(vec[1].getActivityName(), "Palestra");
    EXPECT_EQ(vec[2].getActivityName(), "Studio");
}

TEST_F(ActivityTrackerTest, addActivity_differentDateActivity_organized) {
    tracker->addActivity(date1, *cane);
    tracker->addActivity(date1, *palestra);
    tracker->addActivity(date2, *studio);

    EXPECT_EQ(tracker->getActivitiesForDate(date1).size(), 2);
    EXPECT_EQ(tracker->getActivitiesForDate(date2).size(), 1);

    std::list<Activity> activitiesDate1 = tracker->getActivitiesForDate(date1);
    bool found1 = false;
    bool found2 = false;

    for (const auto& act : activitiesDate1) {
        if (act.getActivityName() == "Cane") found1 = true;
        if (act.getActivityName() == "Palestra") found2 = true;
    }

    EXPECT_TRUE(found1);
    EXPECT_TRUE(found2);

    EXPECT_EQ(tracker->getActivitiesForDate(date2).front().getActivityName(), "Studio");
}

TEST_F(ActivityTrackerTest, removeActivity_correctlyRemoved) {
    tracker->addActivity(date1, *cane);
    tracker->addActivity(date1, *palestra);
    tracker->addActivity(date2, *studio);

    tracker->removeActivity(date1, *palestra);

    std::list<Activity> activities = tracker->getActivitiesForDate(date1);
    bool found = false;
    for (const auto& act : activities) {
        if (act.getActivityName() == "Palestra") {
            found = true;
            break;
        }
    }
    EXPECT_FALSE(found);
}

TEST_F(ActivityTrackerTest, HasActivitiesForDate_ReturnsCorrectBoolean) {
    tracker->addActivity(date1, *cane);

    EXPECT_TRUE(tracker->hasActivitiesForDate(date1));
    EXPECT_FALSE(tracker->hasActivitiesForDate(date2));

    QDate absent {2028, 1, 1};
    EXPECT_FALSE(tracker->hasActivitiesForDate(absent));
}

TEST_F(ActivityTrackerTest, GetAllActivities_ReturnsCompleteMap) {
    tracker->addActivity(date1, *cane);
    tracker->addActivity(date1, *palestra);
    tracker->addActivity(date2, *studio);

    std::map<QDate, std::list<Activity>> allActivities = tracker->getAllActivities();

    ASSERT_EQ(allActivities.size(), 2);
    EXPECT_EQ(allActivities[date1].size(), 2);
    EXPECT_EQ(allActivities[date2].size(), 1);

    bool found = false;
    for (const auto& act : allActivities[date1]) {
        if (act.getActivityName() == "Cane") {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}