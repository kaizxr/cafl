#pragma once
#include "src/Sandbox/SandboxObject.h"
#include <QMenu>

class QGraphicsItem;
class ContextMenu : public QMenu
{
public:
    ContextMenu(QGraphicsItem* item, QWidget *parent = nullptr);
    ~ContextMenu();
private:
    QGraphicsItem* item;
private slots:
    void makeInitial();
    void makeFinal();
    void rename();
    void remove();
};