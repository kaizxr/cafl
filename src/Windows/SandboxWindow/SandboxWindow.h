#pragma once
#ifndef SANDBOXWINDOW_H
#define SANDBOXWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SandboxWindow; }
QT_END_NAMESPACE

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
    void initActions();
    Ui::SandboxWindow *ui;
};
#endif // SANDBOXWINDOW_H
