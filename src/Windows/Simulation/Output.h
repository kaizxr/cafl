#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QGraphicsView>

namespace Ui {
    class Output;
}
namespace Window
{
    namespace Simulation
    {
        class Output : public QWidget
        {
            Q_OBJECT

        public:
            explicit Output(QWidget *parent = nullptr);
            ~Output();

            void initUI();
            void setLabelText(QString text);
            virtual void keyPressEvent(QKeyEvent* event) override;

        private:
            QLabel text;
            QTableWidget* table;
            QGraphicsView* graphicsView;
            Ui::Output *ui;

        private slots:
            void exit();
            void run();
        };
    }
}

#endif // OUTPUT_H
