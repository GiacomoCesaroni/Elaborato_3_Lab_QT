#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QTime>


class Activity {
private:
    QString activityName;
    QString description;
    QTime timeStart;
    QTime timeEnd;

public:
    Activity(const QString &activityName, const QString &description,
             QTime timeStart, QTime timeEnd);

    QTime getTimeStart() const;
    QTime getTimeEnd() const;
    QString getActivityName() const;
    QString getDescription() const;

    bool operator==(const Activity &other) const;

};



#endif //ACTIVITY_H
