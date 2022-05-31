#include "playgroundwindow.h"
#include "ui_playgroundwindow.h"
#include "src/Sandbox/GraphicsView.h"
#include "src/Sandbox/Buttons/ToolButtonGroup.h"
#include "src/Windows/WindowsManager.h"
#include "src/Sandbox/ToolsManager.h"
#include "src/Playground/PlaygroundManager.h"
#include "src/Sandbox/ContextMenu/ContextMenu.h"
#include "src/Automata/Helpers/SimulateHelper.h"
#include <QMessageBox>
#include "src/Utils/SingletonManager.h"

PlaygroundWindow::PlaygroundWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlaygroundWindow)
{
    ui->setupUi(this);

    init();
    initActions();
}

PlaygroundWindow::~PlaygroundWindow()
{
    delete ui;
}

void PlaygroundWindow::initUI()
{
    qInfo("initUI %d:%d",ui->mainFrame->width(),ui->mainFrame->height());
    graphicsView->setGeometry(QRect(0,0,ui->mainFrame->width(), ui->mainFrame->height()));
    auto instance = ToolButtonGroup::getInstance(ui->frame);
    buttonGroup = instance;

    qInfo("%d",playgroundManager->getCurrentTaskId());
    std::string title = playgroundManager->getCurrentTaskData()["title"];
    std::string desc = playgroundManager->getCurrentTaskData()["desc"];
    ui->taskTitle->setText(title.c_str());
    ui->taskDesc->setText(desc.c_str());
}

GraphicsView* PlaygroundWindow::getGraphicsView()
{
    return graphicsView.get();
}

void PlaygroundWindow::init()
{
    graphicsView = std::make_shared<GraphicsView>(ui->mainFrame);
    graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    graphicsView->setFocus();
    graphicsView->show();
    setMouseTracking(true);
    playgroundManager = std::make_shared<PlaygroundManager>();
}

void PlaygroundWindow::initActions()
{
    connect(ui->actionRetry,     &QAction::triggered, this, &PlaygroundWindow::retry       );
    connect(ui->actionExit,      &QAction::triggered, this, &PlaygroundWindow::exit             );
    connect(ui->actionSelectAll, &QAction::triggered, this, &PlaygroundWindow::selectAllObjects );
    connect(ui->actionSelect,    &QAction::triggered, this, &PlaygroundWindow::selectTool       );
    connect(ui->actionNode,      &QAction::triggered, this, &PlaygroundWindow::nodeTool         );
    connect(ui->actionEdge,      &QAction::triggered, this, &PlaygroundWindow::edgeTool         );
    connect(ui->actionHand,      &QAction::triggered, this, &PlaygroundWindow::handTool         );
    connect(ui->actionTest,      &QAction::triggered, this, &PlaygroundWindow::test         );

    connect(ui->clearButton,     &QPushButton::pressed, this, &PlaygroundWindow::retry       );
    connect(ui->checkButton,     &QPushButton::pressed, this, &PlaygroundWindow::test       );
    connect(graphicsView.get(), SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(requestContextMenu(const QPoint&))    );
}

void PlaygroundWindow::reload()
{
    graphicsView->reload();
}

void PlaygroundWindow::resizeEvent(QResizeEvent* event)
{
    graphicsView->setGeometry(QRect(0,0,ui->mainFrame->width(),ui->mainFrame->height()));
}

void PlaygroundWindow::retry()
{
    reload();
}

void PlaygroundWindow::exit()
{
    QApplication::quit();
}

void PlaygroundWindow::selectAllObjects()
{
    if (graphicsView)
        graphicsView->selectAllObjects();
}

void PlaygroundWindow::selectTool()
{
    const auto& toolType = ToolsManager::eToolType::SELECT;
    TOOLS->setToolType(toolType);
    TOOLBOX->toggleButtonGroup((int)toolType);
}

void PlaygroundWindow::nodeTool()
{
    const auto& toolType = ToolsManager::eToolType::NODE;
    TOOLS->setToolType(toolType);
    TOOLBOX->toggleButtonGroup((int)toolType);
}

void PlaygroundWindow::edgeTool()
{
    const auto& toolType = ToolsManager::eToolType::EDGE;
    TOOLS->setToolType(toolType);
    TOOLBOX->toggleButtonGroup((int)toolType);
}

void PlaygroundWindow::handTool()
{
    const auto& toolType = ToolsManager::eToolType::HAND;
    TOOLS->setToolType(toolType);
    TOOLBOX->toggleButtonGroup((int)toolType);
}

#include <iostream>
void PlaygroundWindow::test()
{
    const auto& data = playgroundManager->getCurrentTaskData();
    std::cout << std::setw(4) << data << std::endl;
    QList<QString> inputs;
    for (const auto& input : data["inputs"])
    {
        std::string in(input);
        inputs.append(in.c_str());
    }
    if (graphicsView)
        SIMULATE->startMultipleRun(inputs);
    QList<QString> receivedOut;
    QList<QString> expectedOut;
    for (auto output : SIMULATE->outputs)
    {
        if (output != "REJECTED")
        {
            receivedOut.append("ACCEPTED");
        }
        else
            receivedOut.append("REJECTED");
    }
    bool accepted = true;
    for (const auto& output : data["outputs"])
    {
        bool out(output);
        if (out)
            expectedOut.append("ACCEPTED");
        else
            expectedOut.append("REJECTED");
    }
    for (int i = 0; i < expectedOut.length(); i++)
    {
        if (receivedOut[i] != expectedOut[i])
        {
            accepted = false;
            break;
        }
    }
    QString str;
    if (accepted)
        str = "All tests passed. Correct";
    else
    {
        str = "Not correct.\n Expected output:\n";
        for (int i = 0; i < expectedOut.length(); i++)
        {
            str.append(inputs[i]);
            str.append(". ");
            str.append(expectedOut[i]);
            str.append("\n");
        }
        str.append("Received output:\n");
        for (int i = 0; i < receivedOut.length(); i++)
        {
            str.append(inputs[i]);
            str.append(". ");
            str.append(receivedOut[i]);
            str.append("\n");
        }
    }
    auto box = QMessageBox(QMessageBox::Icon(),"Task checked",str,QMessageBox::Ok);
    box.exec();
    if (accepted)
    {
        playgroundManager->nextTask();
        WINDOWS->changeWindow("playground");
    }
}

void PlaygroundWindow::requestContextMenu(const QPoint& pos)
{
    auto item = graphicsView->itemAt(pos);
    if (!item)
        return;
    ContextMenu menu = ContextMenu(item, this);
    menu.exec(graphicsView->mapToGlobal(pos));
}
