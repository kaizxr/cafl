#include "SimpleTaskCreator.h"
#include "ui_simpletaskcreator.h"
#include "src/Automata/Helpers/SimulateHelper.h"
#include <QKeyEvent>
#include "lib/json.hpp"
#include <fstream>
#include <iostream>
#include "src/Utils/Utils.h"
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "src/Windows/WindowsManager.h"
#include <filesystem>

SimpleTaskCreator::SimpleTaskCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskCreator)
{
    ui->setupUi(this);
}

SimpleTaskCreator::~SimpleTaskCreator()
{
    delete table;
    delete ui;
}

void SimpleTaskCreator::initUI()
{
    table = new QTableWidget(1,2,this);
    table->show();
    table->setFocus();
    table->setGeometry(QRect(10,300,380,190));
    table->setColumnWidth(0,210);
    table->setColumnWidth(1,150);
    connect(ui->exitButton, &QPushButton::clicked, this, &SimpleTaskCreator::exit);
    connect(ui->saveButton, &QPushButton::clicked, this, &SimpleTaskCreator::save);
}

void SimpleTaskCreator::setLabelText(QString text)
{
    
}

void SimpleTaskCreator::keyPressEvent(QKeyEvent* event)
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

void SimpleTaskCreator::exit()
{
    WINDOWS->changeWindow("title");
}

void SimpleTaskCreator::save()
{
    nlohmann::json data;
    QList<QString> inputs;
    QList<bool> outputs;

    int taskId = ui->idEdit->toPlainText().toInt();
    QString titleStr = ui->titleEdir->toPlainText();
    QString descStr = ui->descEdit->toPlainText();
    
    data["title"] = titleStr.toStdString().c_str();
    data["desc"] = descStr.toStdString().c_str();

    int n = table->rowCount();
    for (int row = 0; row < n; row++)
    {
        inputs.append(table->item(row,0)->text());
        outputs.append(table->item(row,1)->text().toInt());
        data["inputs"].push_back(inputs.at(row).toStdString().c_str());
        data["outputs"].push_back(outputs.at(row));
        qInfo("%s-%d", inputs.at(row).toStdString().c_str(), outputs.at(row));
    }

    QDir dir(".");
    std::cout << dir.absolutePath().toStdString().c_str() << std::endl;
    std::string taskPath(strFormat("res/tasks/task_%d/",taskId));
    std::filesystem::path taskDir(taskPath);
    if (!(std::filesystem::exists(taskDir)))
    {
        std::cout << "dir doesn't exist" << std::endl;

        if (std::filesystem::create_directories(taskDir))
            std::cout << "dir created" << std::endl;
    }
    QString filename(strFormat("%s/res/tasks/task_%d/task_%d.json",dir.absolutePath().toStdString().c_str(),taskId,taskId).c_str());

    std::cout << filename.toStdString().c_str() << std::endl;
    std::ofstream out(filename.toStdString());

    out << std::setw(4) << data << std::endl;
    out.close();
}
