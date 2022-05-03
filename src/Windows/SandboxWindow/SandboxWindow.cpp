#include "SandboxWindow.h"
#include "ui_sandboxwindow.h"

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

SandboxWindow::SandboxWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SandboxWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->centralwidget);

    initActions();
}

SandboxWindow::~SandboxWindow()
{
    delete ui;
    qInfo("~SandboxWindow finished");
}

void SandboxWindow::initActions()
{
    connect(ui->actionNewFile,  &QAction::triggered, this, &SandboxWindow::newFile);
    connect(ui->actionOpenFile, &QAction::triggered, this, &SandboxWindow::openFile);
    connect(ui->actionSaveAs,   &QAction::triggered, this, &SandboxWindow::saveAs);
    connect(ui->actionExit,     &QAction::triggered, this, &SandboxWindow::exit);
    connect(ui->actionCopy,     &QAction::triggered, this, &SandboxWindow::copy);
    connect(ui->actionPaste,    &QAction::triggered, this, &SandboxWindow::paste);
    connect(ui->actionCut,      &QAction::triggered, this, &SandboxWindow::cut);
    connect(ui->actionUndo,     &QAction::triggered, this, &SandboxWindow::undo);
    connect(ui->actionRedo,     &QAction::triggered, this, &SandboxWindow::redo);
}

void SandboxWindow::newFile()
{
    qInfo("Sandbox::newFile()");
    // ui->textEdit->setText(QString());
}


void SandboxWindow::openFile()
{
    qInfo("Sandbox::openFile()");
    // QString filename = QFileDialog::getOpenFileName(this, QString("Open the file"));
    // QFile file(filename);
    // curFileName = filename;
    // if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    //     QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
    //     return;
    // }
    // setWindowTitle(filename);
    // QTextStream in(&file);
    // QString text = in.readAll();
    // ui->textEdit->setText(text);
    // file.close();
}


void SandboxWindow::saveAs()
{
    qInfo("Sandbox::saveAs()");
    // QString filename = QFileDialog::getSaveFileName(this, QString("Save as"));
    // QFile file(filename);
    // if (!file.open(QFile::WriteOnly | QFile::Text)) {
    //     QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
    //     return;
    // }
    // curFileName = filename;
    // setWindowTitle(filename);
    // QTextStream out(&file);
    // QString text = ui->textEdit->toPlainText();
    // out << text;
    // file.close();
}

void SandboxWindow::exit()
{
    qInfo("Sandbox::exit()");
    QApplication::quit();
}

void SandboxWindow::copy()
{
    qInfo("Sandbox::copy()");
    // ui->textEdit->copy();
}

void SandboxWindow::paste()
{
    qInfo("Sandbox::paste()");
    // ui->textEdit->paste();
}

void SandboxWindow::cut()
{
    qInfo("Sandbox::cut()");
    // ui->textEdit->cut();
}

void SandboxWindow::undo()
{
    qInfo("Sandbox::undo()");
    // ui->textEdit->undo();
}

void SandboxWindow::redo()
{
    qInfo("Sandbox::redo()");
    // ui->textEdit->redo();
}



