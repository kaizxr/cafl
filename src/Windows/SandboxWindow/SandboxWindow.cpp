#include "SandboxWindow.h"
#include "ui_sandboxwindow.h"
#include "src/Utils/Utils.h"

// initUI()
#include "src/Sandbox/GraphicsView.h"
#include "src/Sandbox/Node.h"
#include "src/Utils/Constants.h"
#include "src/Sandbox/Buttons/ToggleButton.h"
#include "src/Sandbox/Buttons/ButtonGroup.h"

#include <QGraphicsView>
#include <QGraphicsScene>

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
#ifdef DEBUG
    qInfo("SandboxWindow constructor");
#endif
    ui->setupUi(this);

    init();
    initActions();
}

SandboxWindow::~SandboxWindow()
{
    delete ui;
#ifdef DEBUG
    qInfo("~SandboxWindow finished");
#endif
}

void SandboxWindow::initUI()
{
#ifdef DEBUG
    qInfo("initUI");
#endif
    graphicsView->setGeometry(QRect(0,0,ui->mainFrame->width(), ui->mainFrame->height()));
    graphicsView->setSceneRect(QRectF(0,0,ui->mainFrame->width(), ui->mainFrame->height()));

    graphicsView->addNode(150,450);
    graphicsView->addNode(400,450);

    buttonGroup = std::make_shared<ButtonGroup>(ui->frame);

#ifdef DEBUG
    qInfo(strFormat("scene rect = %f:%f:%f:%f\n ", graphicsView->sceneRect().x(), graphicsView->sceneRect().y(), graphicsView->sceneRect().width(), graphicsView->sceneRect().height()).c_str());
#endif
}

void SandboxWindow::init()
{
    graphicsView = std::make_shared<GraphicsView>(QRect(0,0,ui->mainFrame->width(), ui->mainFrame->height()),ui->mainFrame);
    graphicsView->setGeometry(QRect(0,0,ui->mainFrame->width(), ui->mainFrame->height()));
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

void SandboxWindow::resizeEvent(QResizeEvent* event)
{
    graphicsView->setGeometry(QRect(0,0,ui->mainFrame->width(),ui->mainFrame->height()));
}

void SandboxWindow::mouseMoveEvent(QMouseEvent* event)
{
    std::string temp;
    int x = event->pos().x() - ui->mainFrame->x();
    int y = event->pos().y() - ui->mainFrame->y();

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > ui->mainFrame->width()) x = ui->mainFrame->width();
    if (y > ui->mainFrame->height()) y = ui->mainFrame->height();

    // temp = strFormat("mainFrame pos = %d:%d:%d:%d\n mouse pos = %d:%d\n ",
    //     ui->mainFrame->x(), ui->mainFrame->y(), ui->mainFrame->width(), ui->mainFrame->height(),
    //     x, y);
    // ui->label_3->setText(QString(temp.c_str()));
}

void SandboxWindow::newFile()
{
#ifdef DEBUG
    qInfo("Sandbox::newFile()");
#endif
    // ui->textEdit->setText(QString());
}

void SandboxWindow::openFile()
{
#ifdef DEBUG
    qInfo("Sandbox::openFile()");
#endif
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
#ifdef DEBUG
    qInfo("Sandbox::saveAs()");
#endif
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
#ifdef DEBUG
    qInfo("Sandbox::exit()");
#endif
    QApplication::quit();
}

void SandboxWindow::copy()
{
#ifdef DEBUG
    qInfo("Sandbox::copy()");
#endif
    // ui->textEdit->copy();
}

void SandboxWindow::paste()
{
#ifdef DEBUG
    qInfo("Sandbox::paste()");
#endif
    // ui->textEdit->paste();
}

void SandboxWindow::cut()
{
#ifdef DEBUG
    qInfo("Sandbox::cut()");
#endif
    // ui->textEdit->cut();
}

void SandboxWindow::undo()
{
#ifdef DEBUG
    qInfo("Sandbox::undo()");
#endif
    // ui->textEdit->undo();
}

void SandboxWindow::redo()
{
#ifdef DEBUG
    qInfo("Sandbox::redo()");
#endif
    // ui->textEdit->redo();
}



