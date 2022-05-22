#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>
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

            void init();
            void setLabelText(QString text);

        private:
            QLabel text;
            QGraphicsView* graphicsView;
            Ui::Output *ui;

        public:
            enum class eType
            {
                NONE = -1,
                FAST_RUN,
                SIMULATE
            };
        };
    }
}

#endif // OUTPUT_H
