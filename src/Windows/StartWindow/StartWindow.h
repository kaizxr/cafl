#pragma once
#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void openSandbox();
    void openPlayground();
    void openTConstructor();

private:
    void initActions();
    Ui::StartWindow *ui;
};
#endif // STARTWINDOW_H
