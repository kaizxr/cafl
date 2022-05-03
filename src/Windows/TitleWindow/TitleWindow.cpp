#include "TitleWindow.h"
#include "ui_titlewindow.h"

#include "src/Windows/WindowsManager.h"

#include <QFile>
#include <QFileDialog>
#include <QPushButton>

TitleWindow::TitleWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TitleWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->centralwidget);

    initActions();
}

TitleWindow::~TitleWindow()
{
    delete ui;
    qInfo("~TitleWindow finished");
}

void TitleWindow::initActions()
{
    connect(ui->newButton,  &QPushButton::clicked, this, &TitleWindow::newProject);
    connect(ui->openButton, &QPushButton::clicked, this, &TitleWindow::openProject);
    connect(ui->faRButton,  &QPushButton::clicked, this, &TitleWindow::faType);
    connect(ui->pdaRButton, &QPushButton::clicked, this, &TitleWindow::pdaType);
    connect(ui->tmRButton,  &QPushButton::clicked, this, &TitleWindow::tmType);
}

void TitleWindow::newProject()
{
    qInfo("newProject");

    WINDOWS()->changeWindow("sandbox");
}

void TitleWindow::openProject()
{
    qInfo("openProject");

    QString filename = QFileDialog::getOpenFileName(this);
    if (!filename.isEmpty())
    {
        WINDOWS()->changeWindow("sandbox");
    }
    // QFile file(filename);
    // if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    //     QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
    //     return;
    // }
}

void TitleWindow::faType()
{
    qInfo("faType");
}

void TitleWindow::pdaType()
{
    qInfo("pdaType");
}

void TitleWindow::tmType()
{
    qInfo("tmType");
}

