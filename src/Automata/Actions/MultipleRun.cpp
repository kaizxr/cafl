#include "MultipleRun.h"
#include "src/Utils/Constants.h"
#include "src/Automata/Configuration.h"
#include "src/Automata/Simulator.h"
#include "src/Automata/State.h"
#include "src/Automata/FSA/FSAStepByStepSimulator.h"

using namespace AA::Actions;

MultipleRun::MultipleRun(AA::Automata* automata, QList<QString> inputs)
    : FastRun(automata), inputs(inputs)
{
    name = "Multiple run";
}

MultipleRun::~MultipleRun()
{
}
bool MultipleRun::confirmContinue(int generated)
{

}

void MultipleRun::preHandle()
{
    qInfo("start MultipleRun::preHandle()");
    auto configs = QList<AA::Configuration*>();
    auto simulator = new FSA::StepByStepSimulator(automata);

    for (auto input : inputs)
    {   
        qInfo("input %s",input.toStdString().c_str());
        if (input.isEmpty())
            input = "λ";
        configs = simulator->getInitialConfigs(input);

        handleInteraction(automata,simulator,configs,nullptr);
    }
    qInfo("end MultipleRun::preHandle()");
}

void MultipleRun::handleInteraction(Automata* automata, AA::Simulator* simulator, QList<AA::Configuration*> configs, QInputDialog* initialInput)
{
    qInfo("fast run handle");
    int numberGenerated = 0;
    int warningGenerated = CONST["Simulate"]["WarningStep"];
    int numberAccepted = 0;
    while (configs.length() > 0) {
        numberGenerated += configs.length();
        if (numberGenerated >= warningGenerated) {
            // if (!confirmContinue(numberGenerated))
            //     return;
            while (numberGenerated >= warningGenerated)
                warningGenerated *= 2;
        }
        // Get the next batch of configurations.
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
        qInfo("numbersAccepted == 0");
        outputs.append("NOT ACCEPTED");
        return;
    }
}

bool MultipleRun::reportConfiguration(AA::Configuration* conf)
{
    // CREATE OUTPUT WINDOW WITH HIERARCHY
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
    outputs.append(str);

    delete conf;

    return true;
}

QList<QString> MultipleRun::getOutputs() const
{
    return outputs;
}
