#include "MainWindow.h"
#include "ActivityTracker.h"
#include "Activity.h"

#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>


ActivityDialog::ActivityDialog(const QString &title, const QString &text, QWidget *parent)
    : QDialog(parent), textBrowser(nullptr), closeButton(nullptr) {

    setWindowTitle(title);
    resize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);

    textBrowser = new QTextBrowser(this);
    textBrowser->setPlainText(text);
    textBrowser->setReadOnly(true);

    closeButton = new QPushButton("Chiudi", this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

    layout->addWidget(textBrowser);
    layout->addWidget(closeButton);
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      spinDay(nullptr), spinMonth(nullptr), spinYear(nullptr),
      timeStartEdit(nullptr), timeEndEdit(nullptr),
      txtTitle(nullptr), txtDescription(nullptr),
      btnAdd(nullptr), btnRemove(nullptr), btnShowDay(nullptr), btnShowAll(nullptr),
      tracker(nullptr) {

    tracker = new ActivityTracker();

    setupUI();
    setupConnections();

    setWindowTitle("Activity Tracker");
    resize(1000, 700);
}

MainWindow::~MainWindow() {
    delete tracker;
}