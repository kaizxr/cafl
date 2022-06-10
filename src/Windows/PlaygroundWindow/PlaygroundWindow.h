#pragma once
#ifndef PLAYGROUNDWINDOW_H
#define PLAYGROUNDWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PlaygroundWindow; }
QT_END_NAMESPACE

class PlaygroundManager;
class Node;
class GraphicsView;
class ToolButtonGroup;
class PlaygroundWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlaygroundWindow(QWidget *parent = nullptr);
    ~PlaygroundWindow();

    void initUI();
    GraphicsView* getGraphicsView();

private slots:
    void retry();
    void backToStartWindow();
    void exit();
    void selectAllObjects();
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
    
    std::shared_ptr<GraphicsView> graphicsView;
    std::shared_ptr<Node> node0; 
    ToolButtonGroup* buttonGroup;
    std::shared_ptr<PlaygroundManager> playgroundManager;
    Ui::PlaygroundWindow *ui;
};

#endif // PLAYGROUNDWINDOW_H
