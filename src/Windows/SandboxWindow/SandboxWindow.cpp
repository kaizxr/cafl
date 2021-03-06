#include "SandboxWindow.h"
#include "ui_sandboxwindow.h"
#include "src/Utils/Utils.h"

// initUI()
#include "src/Sandbox/GraphicsView.h"
#include "src/Sandbox/Node.h"
#include "src/Sandbox/Edge/BaseEdge.h"
#include "src/Utils/Constants.h"
#include "src/Sandbox/Buttons/ToggleButton.h"
#include "src/Sandbox/Buttons/ToolButtonGroup.h"

#include "src/Windows/WindowsManager.h"
#include "src/Sandbox/ToolsManager.h"

#include "src/Sandbox/ContextMenu/ContextMenu.h"
#include "src/Automata/Helpers/SimulateHelper.h"
#include "src/Windows/Simulation/MultipleInput.h"

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QMouseEvent>

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <QMessageBox>


SandboxWindow::SandboxWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SandboxWindow)
{
    qInfo("sandbox window constructor");
    ui->setupUi(this);

    init();
    initActions();
}

SandboxWindow::~SandboxWindow()
{
    delete ui;
}

void SandboxWindow::initUI()
{
    graphicsView->setGeometry(QRect(0,0,ui->mainFrame->width(), ui->mainFrame->height()));
    
    buttonGroup = std::shared_ptr<ToolButtonGroup>(new ToolButtonGroup(ui->frame));
}

void SandboxWindow::init()
{
    graphicsView = std::make_shared<GraphicsView>(ui->mainFrame);
    graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    graphicsView->setFocus();
    setMouseTracking(true);
}

void SandboxWindow::saveJson(nlohmann::json data)
{
    QString filter = "JSON file (*.json)";
    QString filename = QFileDialog::getSaveFileName(this, QString("Save as"),QString(),filter,&filter);
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    curFilename = filename;
    auto start = curFilename.lastIndexOf("/")+1;
    auto end = curFilename.lastIndexOf(".");
    curFilename = curFilename.mid(start,end-start);
    setWindowTitle(curFilename);
    ui->titleLabel->setText(curFilename);

    std::ofstream out(filename.toStdString());
    out << std::setw(4) << data << std::endl;
    file.close();
}

void SandboxWindow::openGraph()
{
    QString filter = "JSON file (*.json)";
    QString filename = QFileDialog::getOpenFileName(this, QString("Open the file"),QString(),filter,&filter);
    QFile file(filename);

    curFilename = filename;
    auto start = curFilename.lastIndexOf("/")+1;
    auto end = curFilename.lastIndexOf(".");
    curFilename = curFilename.mid(start,end-start);
    setWindowTitle(curFilename);
    ui->titleLabel->setText(curFilename);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    std::ifstream in(filename.toStdString().c_str());
    nlohmann::json data;
    in >> data;
    file.close();

    graphicsView->openFromJson(data);
}

void SandboxWindow::initActions()
{
    connect(ui->actionNewProject,    &QAction::triggered, this, &SandboxWindow::newProject        );
    connect(ui->actionOpenProject,   &QAction::triggered, this, &SandboxWindow::openProject       );
    connect(ui->actionSaveAs,        &QAction::triggered, this, &SandboxWindow::saveAs            );
    connect(ui->actionExit,          &QAction::triggered, this, &SandboxWindow::exit              );
    connect(ui->actionStartWindow,   &QAction::triggered, this, &SandboxWindow::backToStartWindow );
    connect(ui->actionSelectAll,     &QAction::triggered, this, &SandboxWindow::selectAllObjects  );
    connect(ui->actionRemove,        &QAction::triggered, this, &SandboxWindow::removeSelected    );
    connect(ui->actionMakeFinal,     &QAction::triggered, this, &SandboxWindow::makeFinal         );
    connect(ui->actionMakeInitial,   &QAction::triggered, this, &SandboxWindow::makeInitial       );
    connect(ui->actionSelect,        &QAction::triggered, this, &SandboxWindow::selectTool        );
    connect(ui->actionNode,          &QAction::triggered, this, &SandboxWindow::nodeTool          );
    connect(ui->actionEdge,          &QAction::triggered, this, &SandboxWindow::edgeTool          );
    connect(ui->actionHand,          &QAction::triggered, this, &SandboxWindow::handTool          );
    connect(ui->actionOneInput,      &QAction::triggered, this, &SandboxWindow::oneInput          );
    connect(ui->actionMultipleInput, &QAction::triggered, this, &SandboxWindow::multipleInput     );

    connect(graphicsView.get(), SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(requestContextMenu(const QPoint&))    );
}

void SandboxWindow::resizeEvent(QResizeEvent* event)
{
    graphicsView->setGeometry(QRect(0,0,ui->mainFrame->width(),ui->mainFrame->height()));
}

void SandboxWindow::newProject()
{
    WINDOWS->changeWindow("sandbox");
}

void SandboxWindow::openProject()
{
    openGraph();
}

void SandboxWindow::saveAs()
{
    if (graphicsView)
        graphicsView->writeToJson();
}

void SandboxWindow::backToStartWindow()
{
    WINDOWS->changeWindow("title");
}

void SandboxWindow::exit()
{
    QApplication::quit();
}

void SandboxWindow::selectAllObjects()
{
    if (graphicsView)
        graphicsView->selectAllObjects();
}

void SandboxWindow::removeSelected()
{
    if (graphicsView)
        graphicsView->removeObjects();
}


void SandboxWindow::makeFinal()
{
    if (graphicsView)
        graphicsView->tryMakeFinal();
}

void SandboxWindow::makeInitial()
{
    if (graphicsView)
        graphicsView->tryMakeInitial();
}

void SandboxWindow::selectTool()
{
    const auto& toolType = ToolsManager::eToolType::SELECT;
    TOOLS->setToolType(toolType);
    buttonGroup->toggleButtonGroup((int)toolType);
}

void SandboxWindow::nodeTool()
{
    const auto& toolType = ToolsManager::eToolType::NODE;
    TOOLS->setToolType(toolType);
    buttonGroup->toggleButtonGroup((int)toolType);
}

void SandboxWindow::edgeTool()
{
    const auto& toolType = ToolsManager::eToolType::EDGE;
    TOOLS->setToolType(toolType);
    buttonGroup->toggleButtonGroup((int)toolType);
}

void SandboxWindow::handTool()
{
    const auto& toolType = ToolsManager::eToolType::HAND;
    TOOLS->setToolType(toolType);
    buttonGroup->toggleButtonGroup((int)toolType);
}

void SandboxWindow::oneInput()
{
    if (graphicsView)
        SIMULATE->startFastRun();
}

void SandboxWindow::multipleInput()
{    
    auto window = new Window::Simulation::MultipleInput();
    window->show();
    window->initUI();
}

void SandboxWindow::requestContextMenu(const QPoint& pos)
{
    auto item = graphicsView->itemAt(pos);
    if (!item)
        return;
    qInfo("requestContextMenu");
    ContextMenu menu = ContextMenu(item, this);

    menu.exec(graphicsView->mapToGlobal(pos));
}


