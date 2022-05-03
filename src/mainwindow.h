#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void connectActions();
    Ui::MainWindow *ui;
    QString curFileName;
};
#endif // MAINWINDOW_H
