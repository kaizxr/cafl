#include "CheckerRun.h"
#include "src/Automata/Configuration.h"
#include "src/Automata/State.h"

using namespace AA::Actions;

CheckerRun::CheckerRun(AA::Automata* automata, QList<QString> inputs)
    : MultipleRun(automata, inputs)
{
    name = "Checker run";
}

CheckerRun::~CheckerRun()
{

}

bool CheckerRun::reportConfiguration(AA::Configuration* conf)
{
    QString initstr, str;
    QMessageBox::StandardButtons buttons = QMessageBox::Ok;
    while (conf)
    {
        initstr += QString::number(conf->getCurrentState()->getId());
        conf = conf->getParent();
        if (conf)
            initstr += ";";
    }
    auto arr = initstr.split(";");
    auto it = arr.end();
    for (it; it != arr.begin();)
    {
        it--;
        str += *it;
        str += "->";
    }
    str = str.left(str.length()-2);
    qInfo("found str %s", str.toStdString().c_str());
    outputs.append("ACCEPTED");

    delete conf;

    return true;
}
