#pragma once
#include <QCheckBox>

class ToggleButton : public QCheckBox
{
public:
    ToggleButton(QRect rect, QWidget *parent = nullptr);
    virtual ~ToggleButton();
protected:
    // virtual void paintEvent(QPaintEvent* event) override;
private slots:
    void reactToToggle(bool checked);
};