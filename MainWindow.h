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

class MainWindow {

};



#endif //MAINWINDOW_H
