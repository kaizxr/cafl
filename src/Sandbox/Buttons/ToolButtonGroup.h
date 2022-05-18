#pragma once
#include <QButtonGroup>

#define TOOLBOX ToolButtonGroup::getInstance()

class QWidget;
class ToolButtonGroup : public QButtonGroup
{
public:
    static ToolButtonGroup* getInstance(QWidget* widgetParent = nullptr);
    static void cleanup();
    ToolButtonGroup(QWidget* widgetParent = nullptr);
    ~ToolButtonGroup();
    int getCurrentActiveId();
private:
    static ToolButtonGroup* instance;
    int currentActiveId;

private slots:
    void reactToToggled(QAbstractButton *button, bool checked);

};