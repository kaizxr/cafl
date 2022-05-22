#pragma once
#include "src/Automata/Configuration.h"
#include <QString>

namespace FSA
{
    class Configuration : public AA::Configuration
    {
    public:
        Configuration(AA::State* state, FSA::Configuration* parent, QString input, QString unprocessedInput);
        ~Configuration();
        QString getInput();
        QString getUnprocessed();
        void setUnprocessedInput(QString unprocessedInput);
        bool isAccepted() override;
        bool isEqualTo(Object* other) override;
    private:
        QString input;
        QString unprocessedInput;
    };
}