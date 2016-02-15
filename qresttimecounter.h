#ifndef QRESTTIMECOUNTER_H
#define QRESTTIMECOUNTER_H

#include <QDialog>

namespace Ui {
class QRestTimeCounter;
}

class QRestTimeCounter : public QDialog
{
    Q_OBJECT

public:
    explicit QRestTimeCounter(QWidget *parent = 0);
    ~QRestTimeCounter();

private:
    Ui::QRestTimeCounter *ui;
};

#endif // QRESTTIMECOUNTER_H
