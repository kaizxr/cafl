#include "FSAStepByStepSimulator.h"
#include "src/Automata/Automata.h"
#include "FSAConfiguration.h"
#include "FSATransition.h"

using namespace FSA;

StepByStepSimulator::StepByStepSimulator(AA::Automata* automata)
    : AA::Simulator(automata)
{
}

StepByStepSimulator::~StepByStepSimulator()
{
}

QList<AA::Configuration*> StepByStepSimulator::getInitialConfigs(QString input)
{
    QList<AA::Configuration*> tConfigs;
    tConfigs.emplace_back(new FSA::Configuration(automata->getInitialState(),nullptr,input,input));
    return tConfigs;
}

QList<AA::Configuration*> StepByStepSimulator::stepConfigs(AA::Configuration* config)
{
    QList<AA::Configuration*> list;
    auto castedConf = dynamic_cast<FSA::Configuration*>(config);
    auto unprocessed = castedConf->getUnprocessed();
    auto input = castedConf->getInput();
    auto curState = castedConf->getCurrentState();
    auto transitions = automata->getTransitionsFromState(curState); 

    for (auto& t : transitions)
    {
        auto transition = dynamic_cast<FSA::Transition*>(t);
        auto transText = transition->getText();
        auto tryAddConf = [&](const QString& str){
            if (unprocessed.startsWith(str))
            {
                QString tInput = "";
                if (transText.length() < unprocessed.length())
                    tInput = unprocessed.right(transText.length());
                auto destState = transition->getDest();
                auto addConf = new FSA::Configuration(destState, castedConf, input, tInput);
                list.append(addConf);
            }
        };
        if (transText.contains(";"))
        {
            const auto textArr = transition->getText().split("; ");
            for (const auto& t : textArr)
            {
                tryAddConf(t);
            }
        }
        else
        {
            tryAddConf(transText);
        }
    }
    return list;
}

bool StepByStepSimulator::isAccepted()
{
    for (auto& c : configs)
    {
        auto conf = dynamic_cast<FSA::Configuration*>(c);
        auto curState = conf->getCurrentState();
        if (conf->getUnprocessed().isEmpty() &&
            automata->isFinalState(curState))
            return true;
    }
    return false;
}

bool StepByStepSimulator::simulateInput(QString input)
{
    configs.clear();
    auto initialConfigs = getInitialConfigs(input);
    for (auto& ic : initialConfigs)
        configs.insert(dynamic_cast<FSA::Configuration*>(ic));
    while (!configs.isEmpty())
    {
        if (isAccepted())
            return true;
        auto addConfs = QList<AA::Configuration*>();
        auto it = configs.begin();
        for (it; it != configs.end(); )
        {
            auto conf = dynamic_cast<FSA::Configuration*>(*it);
            auto confs = stepConfigs(conf);
            addConfs.append(confs);

            delete *it;
            it = configs.erase(it);
        }
        QSet<AA::Configuration*> addSet(addConfs.begin(),addConfs.end());
        configs.unite(addSet);
    }
    return false;
}
