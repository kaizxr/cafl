#include "MultipleInput.h"
#include "ui_multipleinput.h"
#include "src/Automata/Helpers/SimulateHelper.h"
#include <QKeyEvent>

using namespace Window::Simulation;

MultipleInput::MultipleInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultipleInput)
{
    ui->setupUi(this);
}

MultipleInput::~MultipleInput()
{
    delete table;
    delete ui;
}

void MultipleInput::initUI()
{
    table = new QTableWidget(1,2,this);
    table->show();
    table->setFocus();
    table->setGeometry(QRect(10,10,380,240));
    table->setColumnWidth(0,210);
    table->setColumnWidth(1,150);
    connect(ui->exitButton, &QPushButton::clicked, this, &MultipleInput::exit);
    connect(ui->runButton, &QPushButton::clicked, this, &MultipleInput::run);
}

void MultipleInput::setLabelText(QString text)
{
    
}

void MultipleInput::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        int currentRow = table->currentRow();
        if (currentRow + 1 < table->rowCount())
        {
            table->setCurrentCell(currentRow + 1,0);
        }
        else
        {
            table->insertRow(currentRow + 1);
            table->setCurrentCell(currentRow + 1,0);
        }
    }
    if (event->key() == Qt::Key_Delete)
    {
        table->removeRow(table->currentRow());
    }
}

void MultipleInput::exit()
{
    close();
}

void MultipleInput::run()
{
    QList<QString> inputs;
    int n = table->rowCount();
    qInfo("inputs");
    for (int row = 0; row < n; row++)
    {
        inputs.append(table->item(row,0)->text());
        qInfo("%s", inputs.at(row).toStdString().c_str());
    }

    SIMULATE->startMultipleRun(inputs);

    QList<QString> outputs = SIMULATE->outputs;
    for (int row = 0; row < n; row++)
    {
        qInfo("%s", outputs.at(row).toStdString().c_str());
        QTableWidgetItem *item = new QTableWidgetItem(outputs.at(row));
        table->setItem(row,1,item);
    }
}
