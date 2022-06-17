#ifndef MULTIPLEINPUT_H
#define MULTIPLEINPUT_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QGraphicsView>

namespace Ui {
    class MultipleInput;
}
namespace Window
{
    namespace Simulation
    {
        class MultipleInput : public QWidget
        {
            Q_OBJECT

        public:
            explicit MultipleInput(QWidget *parent = nullptr);
            ~MultipleInput();

            void initUI();
            void setLabelText(QString text);
            virtual void keyPressEvent(QKeyEvent* event) override;

        private:
            QLabel text;
            QTableWidget* table;
            QGraphicsView* graphicsView;
            Ui::MultipleInput *ui;

        private slots:
            void exit();
            void run();
        };
    }
}

#endif // MULTIPLEINPUT_H
