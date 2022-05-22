#include "Output.h"
#include "ui_output.h"

#include "FastRun/TraceObject.h"

using namespace Window::Simulation;

Output::Output(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Output)
{
    ui->setupUi(this);
}

Output::~Output()
{
    delete graphicsView;
    delete ui;
}

void Output::init()
{
    graphicsView = new QGraphicsView(this);
    graphicsView->show();
    graphicsView->setFocus();
    graphicsView->setGeometry(QRect(0,0,380,240));
    graphicsView->setScene(new QGraphicsScene(graphicsView));
    graphicsView->setSceneRect(graphicsView->rect());
    auto s = graphicsView->sceneRect();
    qInfo("%f:%f:%f:%f",s.x(),s.y(),s.width(),s.height());

    // FastRun::TraceObject* tr = new FastRun::TraceObject(this);
    // qInfo("tr %d:%d",tr->pos().x(),tr->pos().y());
    // tr->setInput("1|2333455");
    // graphicsView->scene()->addItem(tr);
    // FastRun::TraceObject* tr2 = new FastRun::TraceObject(QPoint(0,60),this);
    // qInfo("tr2 %d:%d",tr2->pos().x(),tr2->pos().y());
    // tr2->setInput("12|333455");
    // graphicsView->scene()->addItem(tr2);
}

void Output::setLabelText(QString text)
{

}
