#include "qresttimecounter.h"
#include "ui_qresttimecounter.h"

QRestTimeCounter::QRestTimeCounter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRestTimeCounter)
{
    ui->setupUi(this);
}

QRestTimeCounter::~QRestTimeCounter()
{
    delete ui;
}
