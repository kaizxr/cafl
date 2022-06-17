#ifndef TASK_CREATOR_H
#define TASK_CREATOR_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QGraphicsView>

namespace Ui {
    class SimpleTaskCreator;
}

class SimpleTaskCreator : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleTaskCreator(QWidget *parent = nullptr);
    ~SimpleTaskCreator();

    void initUI();
    void setLabelText(QString text);
    virtual void keyPressEvent(QKeyEvent* event) override;

private:
    QTableWidget* table;
    Ui::SimpleTaskCreator *ui;

private slots:
    void exit();
    void save();
};

#endif // TASK_CREATOR_H
