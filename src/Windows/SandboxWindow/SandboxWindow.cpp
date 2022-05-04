#include "SandboxWindow.h"
#include "ui_sandboxwindow.h"
#include "src/Utils/Utils.h"

// init()
#include "src/Sandbox/Node.h"
#include "src/Sandbox/GraphicsView.h"

// #include <QGraphicsView>
// #include <QGraphicsScene>

#include <QMouseEvent>

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

    init();
    initActions();
}

SandboxWindow::~SandboxWindow()
{
    delete ui;
    qInfo("~SandboxWindow finished");
}

void SandboxWindow::init()
{
    graphicsView = std::make_shared<GraphicsView>(ui->mainFrame->frameRect());

    node0 = std::make_shared<Node>(200.0,200.0,100.0);
    graphicsView->scene()->addItem(node0.get());

    // qInfo:
    // std::string pos = strFormat("node0 pos = %f:%f\n ", node0->pos().x(), node0->pos().y());
    // qInfo(pos.c_str());
    // std::string wh = strFormat("node0 wh = %f:%f\n ", node0->rect().width(), node0->rect().height());
    // qInfo(wh.c_str());

    setMouseTracking(true);
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

void SandboxWindow::mouseMoveEvent(QMouseEvent* event)
{
    // int x = event->pos().x();
    // int y = event->pos().y();
    int x = event->pos().x() - ui->mainFrame->pos().x();
    int y = event->pos().y() - ui->mainFrame->pos().y();

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > ui->mainFrame->width()) x = ui->mainFrame->width();
    if (y > ui->mainFrame->height()) y = ui->mainFrame->height();

    std::string pos = strFormat("mouse pos = %d:%d\n ", x, y);
    ui->label_3->setText(QString(pos.c_str()));
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



