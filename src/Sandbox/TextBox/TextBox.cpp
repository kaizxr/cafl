#include "TextBox.h"
#include "TextListener.h"
#include <QFocusEvent>

TextBox::TextBox(QRect rect, QString text, bool rename, QWidget *parent)
    : QPlainTextEdit(text,parent), rename(rename)
{
    if (auto listener = dynamic_cast<TextListener*>(parent))
        addListener(listener);
    setGeometry(rect);
    show();
    setFocus();
    if (rename)
        this->selectAll();
}

TextBox::~TextBox()
{
    listeners.clear();
}

void TextBox::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        sendOnTextChanged(0);
        return;
    }
    else if (event->key() == Qt::Key_Escape)
    {
        sendOnTextChanged(2);
        return;
    }

    QPlainTextEdit::keyPressEvent(event);
}

void TextBox::sendOnTextChanged(int code)
{
    if (code == 0 && rename)
        code = 1;
    for (const auto& listener : listeners)
        listener->onTextChanged(code);
}

void TextBox::addListener(TextListener* listener)
{
    if (!listeners.contains(listener))
        listeners.append(listener);
}

void TextBox::removeListener(TextListener* listener)
{
    if (listeners.contains(listener))
        listeners.removeAll(listener);
}

bool TextBox::isRenaming() const
{
    return rename;
}

void TextBox::focusOutEvent(QFocusEvent *e)
{
    if (!toPlainText().isEmpty())
        sendOnTextChanged(0);
    else
        sendOnTextChanged(2);
}
