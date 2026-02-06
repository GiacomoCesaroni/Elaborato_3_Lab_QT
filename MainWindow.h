#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>

class QTextBrowser;
class QPushButton;
class QVBoxLayout;
class QSpinBox;
class QLineEdit;
class QTextEdit;
class QGroupBox;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QTimeEdit;

class ActivityTracker;

class ActivityDialog : public QDialog {
    Q_OBJECT
private:
    QTextBrowser* textBrowser;
    QPushButton* closeButton;

public:
    ActivityDialog(const QString &title, const QString &text, QWidget *parent = nullptr);
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addActivity();
    void removeActivity();
    void showDayActivities();
    void showAllActivities();

private:
    void setupUI();
    void setupConnections();
    void setCurrentDate();
    void setCurrentTime();

    QSpinBox* spinDay;
    QSpinBox* spinMonth;
    QSpinBox* spinYear;

    QTimeEdit* timeStartEdit;
    QTimeEdit* timeEndEdit;

    QLineEdit* txtTitle;
    QTextEdit* txtDescription;

    QPushButton* btnAdd;
    QPushButton* btnRemove;
    QPushButton* btnShowDay;
    QPushButton* btnShowAll;

    ActivityTracker* tracker;
};



#endif //MAINWINDOW_H
