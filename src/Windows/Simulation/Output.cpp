#include "Output.h"
#include "ui_output.h"
#include "src/Automata/Helpers/SimulateHelper.h"
#include <QKeyEvent>

using namespace Window::Simulation;

Output::Output(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Output)
{
    ui->setupUi(this);
}

Output::~Output()
{
    delete table;
    delete ui;
}

void Output::initUI()
{
    table = new QTableWidget(1,2,this);
    table->show();
    table->setFocus();
    table->setGeometry(QRect(0,0,380,240));
    table->setColumnWidth(0,210);
    table->setColumnWidth(1,150);
    connect(ui->exitButton, &QPushButton::clicked, this, &Output::exit);
    connect(ui->runButton, &QPushButton::clicked, this, &Output::run);
}

void Output::setLabelText(QString text)
{
    
}

void Output::keyPressEvent(QKeyEvent* event)
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

void Output::exit()
{
    close();
}

void Output::run()
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
