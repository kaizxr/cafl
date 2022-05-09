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
#ifdef DEBUG
    qInfo("~TitleWindow finished");
#endif
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
#ifdef DEBUG
    qInfo("newProject");
#endif

    WINDOWS->changeWindow("sandbox");
}

void TitleWindow::openProject()
{
#ifdef DEBUG
    qInfo("openProject");
#endif

    QString filename = QFileDialog::getOpenFileName(this);
    if (!filename.isEmpty())
    {
        WINDOWS->changeWindow("sandbox");
    }
    // QFile file(filename);
    // if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    //     QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
    //     return;
    // }
}

void TitleWindow::faType()
{
#ifdef DEBUG
    qInfo("faType");
#endif
}

void TitleWindow::pdaType()
{
#ifdef DEBUG
    qInfo("pdaType");
#endif
}

void TitleWindow::tmType()
{
#ifdef DEBUG
    qInfo("tmType");
#endif
}

