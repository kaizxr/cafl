#include "SimulateHelper.h"
#include "src/Windows/WindowsManager.h"
#include "src/Windows/BaseGraphEditorWindow.h"
//#include "src/Windows/PlaygroundWindow/PlaygroundWindow.h"
//#include "src/Windows/SandboxWindow/SandboxWindow.h"
#include "src/Sandbox/GraphicsView.h"

#include "src/Automata/FSA/FSAAutomata.h"
#include "src/Automata/FSA/FSAConfiguration.h"
#include "src/Automata/FSA/FSATransition.h"
#include "src/Automata/State.h"
#include "src/Automata/Actions/FastRun.h"
#include "src/Automata/Actions/MultipleRun.h"
#include "src/Automata/FSA/FSAStepByStepSimulator.h"

SimulateHelper* SimulateHelper::instance = nullptr;

SimulateHelper* SimulateHelper::getInstance()
{
	if (!instance)
	{
        instance = new SimulateHelper();
    }
	return instance;
}

void SimulateHelper::cleanup()
{
	delete instance;
	instance = nullptr;
}

SimulateHelper::SimulateHelper()
{
}

SimulateHelper::~SimulateHelper()
{
}

void SimulateHelper::startFastRun()
{
    inputs.clear();
    if (auto casted = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
    {
        auto automata = casted->getGraphicsView()->convertToFSA();
    
        auto fr = AA::Actions::FastRun(automata);
        fr.preHandle();
    }
}

void SimulateHelper::startMultipleRun(QList<QString> inputs)
{
    this->inputs = inputs;
    AA::Automata* automata;
    if (auto window = dynamic_cast<BaseGraphEditorWindow*>(WINDOWS->getCurWindow()))
    {
        automata = window->getGraphicsView()->convertToFSA();
    }

    auto ml = AA::Actions::MultipleRun(automata, inputs);
    ml.preHandle();
    outputs = ml.getOutputs();
}
