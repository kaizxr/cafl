#pragma once
#ifndef SANDBOXWINDOW_H
#define SANDBOXWINDOW_H

#include <QMainWindow>
#include "src/Windows/BaseGraphEditorWindow.h"
#include "lib/json.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class SandboxWindow; }
QT_END_NAMESPACE

class Node;
class GraphicsView;
class ToolButtonGroup;
class SandboxWindow : public QMainWindow, public BaseGraphEditorWindow
{
    Q_OBJECT

public:
    SandboxWindow(QWidget *parent = nullptr);
    ~SandboxWindow();

    void initUI();
    void saveJson(nlohmann::json data);
    void openGraph();

private slots:
    void newProject();
    void openProject();
    void saveAs();
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
    void oneInput();
    void multipleInput();
    void requestContextMenu(const QPoint& pos);

private:    
    void init();
    void initActions();

    void resizeEvent(QResizeEvent* event) override;

    QString curFilename;
    std::shared_ptr<Node> node0; 
    Ui::SandboxWindow *ui;
};
#endif // SANDBOXWINDOW_H
