#pragma once
#ifndef PLAYGROUNDWINDOW_H
#define PLAYGROUNDWINDOW_H

#include <QMainWindow>
#include "src/Windows/BaseGraphEditorWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PlaygroundWindow; }
QT_END_NAMESPACE

class PlaygroundManager;
class Node;
class GraphicsView;
class ToolButtonGroup;
class PlaygroundWindow : public QMainWindow, public BaseGraphEditorWindow
{
    Q_OBJECT

public:
    explicit PlaygroundWindow(QWidget *parent = nullptr);
    ~PlaygroundWindow();

    void initUI();

private slots:
    void retry();
    void chooseTask();
    void backToStartWindow();
    void exit();
    void selectAllObjects();
    void removeSelected();
    void makeFinal();
    void makeInitial();
    void selectTool();
    void nodeTool();
    void edgeTool();
    void handTool();
    void test();
    void requestContextMenu(const QPoint& pos);

private:
    void reload();
    void init();
    void initActions();

    void resizeEvent(QResizeEvent* event) override;
    
    std::shared_ptr<Node> node0; 
    std::shared_ptr<PlaygroundManager> playgroundManager;
    Ui::PlaygroundWindow *ui;
};

#endif // PLAYGROUNDWINDOW_H
