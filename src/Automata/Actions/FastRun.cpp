#include "FastRun.h"
#include "src/Utils/Constants.h"
#include "src/Automata/Configuration.h"
#include "src/Automata/Simulator.h"
#include "src/Automata/State.h"
#include "src/Automata/FSA/FSAStepByStepSimulator.h"

using namespace AA::Actions;

FastRun::FastRun(AA::Automata* automata) : Simulate(automata)
{
    name = "Fast run";
}

FastRun::~FastRun()
{
}
bool FastRun::confirmContinue(int generated)
{

}

void FastRun::handleInteraction(Automata* automata, AA::Simulator* simulator, QList<AA::Configuration*> configs, QInputDialog* initialInput)
{
    int numberGenerated = 0;
    int warningGenerated = CONST["Simulate"]["WarningStep"];
    int numberAccepted = 0;
    while (configs.length() > 0) {
        numberGenerated += configs.length();
        if (numberGenerated >= warningGenerated) {
            while (numberGenerated >= warningGenerated)
                warningGenerated *= 2;
        }
        auto next = QList<AA::Configuration*>();
        for (auto& config : configs)
        {
            if (config->isAccepted())
            {
                numberAccepted++;
                if (!reportConfiguration(config))
                {
                    return;
                }
            }
            else
                next.append(simulator->stepConfigs(config));
        }
        configs.clear();
        configs = next;
    }
    if (numberAccepted == 0)
    {
        QMessageBox::StandardButtons buttons = QMessageBox::Ok;
        auto box = new QMessageBox(QMessageBox::Icon(),"Found config","No configs were found",buttons);
        box->exec();
        delete box;
        return;
    }
}

bool FastRun::reportConfiguration(AA::Configuration* conf)
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
    auto box = new QMessageBox(QMessageBox::Icon(),"Found config",str,buttons);
    box->exec();

    delete box;
    delete conf;

    return true;
}
