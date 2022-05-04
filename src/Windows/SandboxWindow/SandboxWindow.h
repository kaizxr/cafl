#pragma once
#ifndef SANDBOXWINDOW_H
#define SANDBOXWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SandboxWindow; }
QT_END_NAMESPACE

class Node;
class GraphicsView;
class SandboxWindow : public QMainWindow
{
    Q_OBJECT

public:
    SandboxWindow(QWidget *parent = nullptr);
    ~SandboxWindow();

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

    void mouseMoveEvent(QMouseEvent* event);
    
    std::shared_ptr<GraphicsView> graphicsView; 
    std::shared_ptr<Node> node0; 
    Ui::SandboxWindow *ui;
};
#endif // SANDBOXWINDOW_H
