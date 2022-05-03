#pragma once
#ifndef TITLEWINDOW_H
#define TITLEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TitleWindow; }
QT_END_NAMESPACE

class TitleWindow : public QMainWindow
{
    Q_OBJECT

public:
    TitleWindow(QWidget *parent = nullptr);
    ~TitleWindow();

private slots:
    void newProject();
    void openProject();
    void faType();
    void pdaType();
    void tmType();

private:
    void initActions();
    Ui::TitleWindow *ui;
};
#endif // TITLEWINDOW_H
