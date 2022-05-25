#pragma once
#ifndef SANDBOXWINDOW_H
#define SANDBOXWINDOW_H

#include <QMainWindow>
#include "lib/json.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class SandboxWindow; }
QT_END_NAMESPACE

class Node;
class GraphicsView;
class ToolButtonGroup;
class SandboxWindow : public QMainWindow
{
    Q_OBJECT

public:
    SandboxWindow(QWidget *parent = nullptr);
    ~SandboxWindow();

    void initUI();
    void saveJson(nlohmann::json data);
    void openGraph();
    GraphicsView* getGraphicsView();

private slots:
    void newProject();
    void openProject();
    void saveAs();
    void exit();
    void selectAllObjects();
    void selectTool();
    void nodeTool();
    void edgeTool();
    void handTool();
    void oneInput();
    void multipleInput();
    void requestContextMenu(const QPoint& pos);

private:    
    void init();
    void initActions();

    void resizeEvent(QResizeEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    QString curFilename;
    // GraphicsView* graphicsView;
    std::shared_ptr<GraphicsView> graphicsView;
    std::shared_ptr<Node> node0; 
    Ui::SandboxWindow *ui;
    std::shared_ptr<ToolButtonGroup> buttonGroup;
};
#endif // SANDBOXWINDOW_H
