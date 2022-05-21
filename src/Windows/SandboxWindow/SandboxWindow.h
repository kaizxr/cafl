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

private slots:
    void newFile();
    void openFile();
    void saveAs();
    void exit();
    void copy();
    void paste();
    void cut();
    void undo();
    void redo();

private:    
    void init();
    void initActions();

    void resizeEvent(QResizeEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    QString curFilename;
    std::shared_ptr<GraphicsView> graphicsView;
    std::shared_ptr<Node> node0; 
    Ui::SandboxWindow *ui;
    std::shared_ptr<ToolButtonGroup> buttonGroup;
};
#endif // SANDBOXWINDOW_H
