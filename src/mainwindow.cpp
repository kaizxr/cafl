#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    curFileName = "";

    connectActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectActions()
{
    connect(ui->actionNewFile,  &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpenFile, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSaveAs,   &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->actionExit,     &QAction::triggered, this, &MainWindow::exit);
    connect(ui->actionCopy,     &QAction::triggered, this, &MainWindow::copy);
    connect(ui->actionPaste,    &QAction::triggered, this, &MainWindow::paste);
    connect(ui->actionCut,      &QAction::triggered, this, &MainWindow::cut);
    connect(ui->actionUndo,     &QAction::triggered, this, &MainWindow::undo);
    connect(ui->actionRedo,     &QAction::triggered, this, &MainWindow::redo);
}

void MainWindow::newFile()
{
    curFileName.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("Open the file"));
    QFile file(filename);
    curFileName = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, QString("Save as"));
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    curFileName = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::exit()
{
    QApplication::quit();
}

void MainWindow::copy()
{
    ui->textEdit->copy();
}

void MainWindow::paste()
{
    ui->textEdit->paste();
}

void MainWindow::cut()
{
    ui->textEdit->cut();
}

void MainWindow::undo()
{
    ui->textEdit->undo();
}

void MainWindow::redo()
{
    ui->textEdit->redo();
}



