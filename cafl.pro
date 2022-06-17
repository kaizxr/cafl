QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Automata/Actions/FastRun.cpp \
    src/Automata/Actions/MultipleRun.cpp \
    src/Automata/Actions/Simulate.cpp \
    src/Automata/FSA/FSAAlphabetRetriever.cpp \
    src/Automata/FSA/FSAAutomata.cpp \
    src/Automata/FSA/FSAConfiguration.cpp \
    src/Automata/FSA/FSAStepByStepSimulator.cpp \
    src/Automata/FSA/FSATransition.cpp \
    src/Automata/Helpers/SimulateHelper.cpp \
    src/Automata/Automata.cpp \
    src/Automata/Configuration.cpp \
    src/Automata/State.cpp \
    src/Automata/Transition.cpp \
    src/Playground/PlaygroundManager.cpp \
    src/Utils/SingletonManager.cpp \
    src/Utils/Constants.cpp \
    src/Sandbox/Buttons/ToolButtonGroup.cpp \
    src/Sandbox/Buttons/ToggleButton.cpp \
    src/Sandbox/ContextMenu/ContextMenu.cpp \
    src/Sandbox/Edge/BaseEdge.cpp \
    src/Sandbox/Edge/Edge.cpp \
    src/Sandbox/Edge/LoopEdge.cpp \
    src/Sandbox/TextBox/TextBox.cpp \
    src/Sandbox/GraphicsView.cpp \
    src/Sandbox/Node.cpp \
    src/Sandbox/SandboxObject.cpp \
    src/Sandbox/Selector.cpp \
    src/Sandbox/ToolsManager.cpp \
    src/Windows/PlaygroundWindow/PlaygroundWindow.cpp \
    src/Windows/SandboxWindow/SandboxWindow.cpp \
    src/Windows/Simulation/MultipleInput.cpp \
    src/Windows/TaskConstructorWindow/SimpleTaskCreator.cpp \
    src/Windows/StartWindow/StartWindow.cpp \
    src/Windows/BaseGraphEditorWindow.cpp \
    src/Windows/WindowsManager.cpp \
    src/main.cpp

HEADERS += \
    lib/json.hpp \
    src/Automata/Actions/FastRun.h \
    src/Automata/Actions/MultipleRun.h \
    src/Automata/Actions/Simulate.h \
    src/Automata/FSA/FSAAlphabetRetriever.h \
    src/Automata/FSA/FSAAutomata.h \
    src/Automata/FSA/FSAConfiguration.h \
    src/Automata/FSA/FSAStepByStepSimulator.h \
    src/Automata/FSA/FSATransition.h \
    src/Automata/Helpers/SimulateHelper.h \
    src/Automata/AlphabetRetriever.h \
    src/Automata/Automata.h \
    src/Automata/Configuration.h \
    src/Automata/Object.h \
    src/Automata/Simulator.h \
    src/Automata/State.h \
    src/Automata/Transition.h \
    src/Playground/PlaygroundManager.h \
    src/Utils/SingletonManager.h \
    src/Utils/Constants.h \
    src/Utils/Utils.h \
    src/Sandbox/Buttons/ToolButtonGroup.h \
    src/Sandbox/Buttons/ToggleButton.h \
    src/Sandbox/ContextMenu/ContextMenu.h \
    src/Sandbox/Edge/BaseEdge.h \
    src/Sandbox/Edge/Edge.h \
    src/Sandbox/Edge/LoopEdge.h \
    src/Sandbox/TextBox/TextBox.h \
    src/Sandbox/TextBox/TextListener.h \
    src/Sandbox/GraphicsView.h \
    src/Sandbox/Node.h \
    src/Sandbox/SandboxObject.h \
    src/Sandbox/Selector.h \
    src/Sandbox/ToolsManager.h \
    src/Windows/PlaygroundWindow/PlaygroundWindow.h \
    src/Windows/SandboxWindow/SandboxWindow.h \
    src/Windows/Simulation/MultipleInput.h \
    src/Windows/TaskConstructorWindow/SimpleTaskCreator.h \
    src/Windows/StartWindow/StartWindow.h \
    src/Windows/BaseGraphEditorWindow.h \
    src/Windows/WindowsManager.h

FORMS += \
    res/ui/multipleinput.ui \
    res/ui/playgroundwindow.ui \
    res/ui/sandboxwindow.ui \
    res/ui/simpletaskcreator.ui \
    res/ui/startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/icons.qrc
