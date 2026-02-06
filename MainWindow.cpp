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