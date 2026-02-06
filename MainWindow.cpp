#include "MainWindow.h"
#include "ActivityTracker.h"
#include "Activity.h"

#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimeEdit>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGroupBox>
#include <QMessageBox>
#include <QDate>
#include <QTimeEdit>
#include <QInputDialog>
#include <QTime>
#include <vector>

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

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout* mainLayout = new QGridLayout(centralWidget);
    mainLayout->setColumnStretch(0, 2);
    mainLayout->setColumnStretch(1, 1);

    QGroupBox* dateGroup = new QGroupBox("DATA", centralWidget);
    QVBoxLayout* dateLayout = new QVBoxLayout(dateGroup);

    QHBoxLayout* dateFields = new QHBoxLayout();
    dateFields->addWidget(new QLabel("giorno", centralWidget));
    spinDay = new QSpinBox(centralWidget);
    spinDay->setRange(1, 31);
    dateFields->addWidget(spinDay);

    dateFields->addWidget(new QLabel("mese", centralWidget));
    spinMonth = new QSpinBox(centralWidget);
    spinMonth->setRange(1, 12);
    dateFields->addWidget(spinMonth);

    dateFields->addWidget(new QLabel("anno", centralWidget));
    spinYear = new QSpinBox(centralWidget);
    spinYear->setRange(2000, 2100);
    dateFields->addWidget(spinYear);

    dateLayout->addLayout(dateFields);
    mainLayout->addWidget(dateGroup, 0, 0);

    QGroupBox* titleGroup = new QGroupBox("Titolo", centralWidget);
    QVBoxLayout* titleLayout = new QVBoxLayout(titleGroup);
    txtTitle = new QLineEdit(centralWidget);
    txtTitle->setPlaceholderText("Inserisci il titolo dell'attività...");
    titleLayout->addWidget(txtTitle);
    mainLayout->addWidget(titleGroup, 1, 0);

    QGroupBox* descGroup = new QGroupBox("Descrizione", centralWidget);
    QVBoxLayout* descLayout = new QVBoxLayout(descGroup);
    txtDescription = new QTextEdit(centralWidget);
    txtDescription->setPlaceholderText("Descrivi l'attività in dettaglio...");
    txtDescription->setMaximumHeight(150);
    descLayout->addWidget(txtDescription);
    mainLayout->addWidget(descGroup, 2, 0);

    QGroupBox* timeGroup = new QGroupBox("Orario", centralWidget);
    QHBoxLayout* timeLayout = new QHBoxLayout(timeGroup);

    timeLayout->addWidget(new QLabel("Inizio:", centralWidget));
    timeStartEdit = new QTimeEdit(centralWidget);
    timeStartEdit->setDisplayFormat("HH:mm");
    timeLayout->addWidget(timeStartEdit);

    timeLayout->addWidget(new QLabel("Fine:", centralWidget));
    timeEndEdit = new QTimeEdit(centralWidget);
    timeEndEdit->setDisplayFormat("HH:mm");
    timeLayout->addWidget(timeEndEdit);

    mainLayout->addWidget(timeGroup, 3, 0);

    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignTop);

    QString buttonStyle =
        "QPushButton {"
        "   padding: 12px;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "   border-radius: 5px;"
        "   margin: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #4d4d4d;"
        "}";

    btnAdd = new QPushButton("Aggiungi Attività", centralWidget);
    btnAdd->setStyleSheet(buttonStyle +
        "QPushButton { background-color: #aecfcf; color: black; }");

    btnRemove = new QPushButton("Rimuovi Attività", centralWidget);
    btnRemove->setStyleSheet(buttonStyle + "QPushButton { background-color: #cfaeae; color: black; }");

    btnShowDay = new QPushButton("Mostra attività del giorno", centralWidget);
    btnShowDay->setStyleSheet(buttonStyle + "QPushButton { background-color: #cdcfae; color: black; }");

    btnShowAll = new QPushButton("Mostra tutte le attività", centralWidget);
    btnShowAll->setStyleSheet(buttonStyle + "QPushButton { background-color: #aecfb8; color: black; }");

    buttonLayout->addWidget(btnAdd);
    buttonLayout->addWidget(btnRemove);
    buttonLayout->addWidget(btnShowDay);
    buttonLayout->addWidget(btnShowAll);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout, 0, 1, 4, 1); // Span 4 righe

    setCurrentDate();
    setCurrentTime();
}

void MainWindow::setupConnections() {
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::addActivity);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::removeActivity);
    connect(btnShowDay, &QPushButton::clicked, this, &MainWindow::showDayActivities);
    connect(btnShowAll, &QPushButton::clicked, this, &MainWindow::showAllActivities);
}

void MainWindow::setCurrentTime() {
    QTime current = QTime::currentTime();
    timeStartEdit->setTime(current);

    QTime plus1Hour = current.addSecs(3600);
    timeEndEdit->setTime(plus1Hour);
}

void MainWindow::addActivity() {
    QString title = txtTitle->text();
    QString description = txtDescription->toPlainText();
    QDate date(spinYear->value(), spinMonth->value(), spinDay->value());
    QTime timeStart = timeStartEdit->time();
    QTime timeEnd = timeEndEdit->time();

    if(title.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Attenzione",
            "Mancata compilazione di tutti i campi!");
        return;
    }

    if (!date.isValid()) {
        QMessageBox::warning(this, "Errore", "Data non valida!");
        return;
    }

    if (timeStart >= timeEnd) {
        QMessageBox::warning(this, "Errore",
            "L'orario di inizio deve essere antecedente all'orario di fine!");
        return;
    }

    Activity activity(title, description, timeStart, timeEnd);

    tracker->addActivity(date, activity);

    QMessageBox::information(this, "Successo",
        "Attività aggiunta con successo!");

    txtTitle->clear();
    txtDescription->clear();
}

void MainWindow::removeActivity() {
    QDate date(spinYear->value(), spinMonth->value(), spinDay->value());

    if (!date.isValid()) {
        QMessageBox::warning(this, "Errore", "Data non valida!");
        return;
    }

    std::list<Activity> activities = tracker->getActivitiesForDate(date);

    if (activities.empty()) {
        QMessageBox::information(this, "Informazione",
            "Nessuna attività per la data selezionata.");
        return;
    }

    QStringList activityStrings;
    for (const Activity& act : activities) {
        activityStrings << QString("%1 (%2 - %3)")
            .arg(act.getActivityName())
            .arg(act.getTimeStart().toString("HH:mm"))
            .arg(act.getTimeEnd().toString("HH:mm"));
    }

    bool ok;
    QString selected = QInputDialog::getItem(this, "Rimuovi Attività","Seleziona l'attività da rimuovere:",activityStrings, 0, false, &ok);

    if (ok && !selected.isEmpty()) {
        int index = activityStrings.indexOf(selected);

        if (index >= 0) {
            std::vector<Activity> vec(activities.begin(), activities.end());
            Activity toRemove = vec[index];

            tracker->removeActivity(date, toRemove);

            QMessageBox::information(this, "Successo",
                "Attività rimossa con successo!");
        }
    }
}

void MainWindow::showDayActivities() {
    QDate date(spinYear->value(), spinMonth->value(), spinDay->value());

    if (!date.isValid()) {
        QMessageBox::warning(this, "Errore", "Data non valida!");
        return;
    }

    std::list<Activity> activities = tracker->getActivitiesForDate(date);

    if (activities.empty()) {
        QMessageBox::information(this, "Informazione",
            "Nessuna attività per la data selezionata.");
        return;
    }

    QString text = QString("Attività per il %1/%2/%3:\n\n")
                       .arg(date.day()).arg(date.month()).arg(date.year());

    int count = 1;
    for (const Activity& act : activities) {
        text += QString("%1. %2\n")
                    .arg(count++)
                    .arg(act.getActivityName());
        text += QString("   Descrizione: %1\n").arg(act.getDescription());
        text += QString("   Orario: %1 - %2\n\n")
                    .arg(act.getTimeStart().toString("HH:mm"))
                    .arg(act.getTimeEnd().toString("HH:mm"));
    }

    text += QString("Totale attività: %1").arg(activities.size());

    ActivityDialog* dialog = new ActivityDialog("Attività del Giorno", text, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
}