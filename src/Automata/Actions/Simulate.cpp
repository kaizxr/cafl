#include "Simulate.h"
#include "src/Automata/FSA/FSAStepByStepSimulator.h"

#include "src/Windows/WindowsManager.h"
#include "src/Windows/SandboxWindow/SandboxWindow.h"

using namespace AA::Actions;

Simulate::Simulate(AA::Automata* automata)
{
    name = "Step...";
    this->automata = automata;
}

Simulate::~Simulate()
{
}

void Simulate::preHandle()
{
    auto dialog = createInputDialog(nullptr);
    auto configs = QList<AA::Configuration*>();
    auto simulator = new FSA::StepByStepSimulator(automata);

    auto input = dialog->textValue();
    qInfo("input %s",input.toStdString().c_str());
    if (input.isEmpty())
        input = "λ";
    configs = simulator->getInitialConfigs(input);

    handleInteraction(automata,simulator,configs,dialog);
}

void Simulate::handleInteraction(Automata* automata, AA::Simulator* simulator, QList<AA::Configuration*> configs, QInputDialog* initialInput)
{
    // TO-DO:
}

AA::Simulator* Simulate::getSimulator(AA::Automata* automata)
{
	return new FSA::StepByStepSimulator(automata);
}

QInputDialog* Simulate::createInputDialog(QString title)
{
    if (title.isEmpty())
        title = "Input";
    auto dialog = new QInputDialog(WINDOWS->getSandboxWindow());
    dialog->setWindowTitle(title);
    dialog->show();
    dialog->exec();
	return dialog;
}

