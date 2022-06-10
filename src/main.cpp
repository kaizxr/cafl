#include "src/Windows/WindowsManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WINDOWS->changeWindow("title");
    
    return a.exec();
}
