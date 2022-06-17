#include "StartWindow.h"
#include "ui_startwindow.h"

#include "src/Windows/WindowsManager.h"

#include <QFile>
#include <QFileDialog>
#include <QPushButton>

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    initActions();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::initActions()
{
    connect(ui->sandboxButton,  &QPushButton::clicked, this, &StartWindow::openSandbox);
    connect(ui->playgroundButton, &QPushButton::clicked, this, &StartWindow::openPlayground);
    connect(ui->taskConstructorButton, &QPushButton::clicked, this, &StartWindow::openTConstructor);
}

void StartWindow::openSandbox()
{
    WINDOWS->changeWindow("sandbox");
}

void StartWindow::openPlayground()
{
    WINDOWS->changeWindow("playground");
}

void StartWindow::openTConstructor()
{
    WINDOWS->changeWindow("taskConstructor");
}


