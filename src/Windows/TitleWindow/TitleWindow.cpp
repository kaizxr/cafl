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
    initActions();
}

TitleWindow::~TitleWindow()
{
    delete ui;
}

void TitleWindow::initActions()
{
    connect(ui->sandboxButton,  &QPushButton::clicked, this, &TitleWindow::openSandbox);
    connect(ui->playgroundButton, &QPushButton::clicked, this, &TitleWindow::openPlayground);
    connect(ui->taskConstructorButton, &QPushButton::clicked, this, &TitleWindow::openTConstructor);
}

void TitleWindow::openSandbox()
{
    WINDOWS->changeWindow("sandbox");
}

void TitleWindow::openPlayground()
{
    WINDOWS->changeWindow("playground");
}

void TitleWindow::openTConstructor()
{
    WINDOWS->changeWindow("taskConstructor");
}


