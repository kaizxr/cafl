#pragma once
#include <QPlainTextEdit>

class TextListener;
class TextBox : public QPlainTextEdit
{
public:
    TextBox(QRect rect, QString text = QString(), bool rename = false, QWidget *parent = nullptr);
    ~TextBox();

    void keyPressEvent(QKeyEvent *event) override;
    void addListener(TextListener* listener);
    void removeListener(TextListener* listener);

    bool isRenaming() const;

private:
    void sendOnTextChanged(int code);
    bool rename;
    QList<TextListener*> listeners;
};