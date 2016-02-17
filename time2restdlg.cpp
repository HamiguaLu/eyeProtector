#include "time2restdlg.h"
#include "ui_time2restdlg.h"
#include <QVBoxLayout>
time2restDlg::time2restDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::time2restDlg)
{
    ui->setupUi(this);

    ui->pushButton->raise();

    ui->lcdNumber->raise();

    setStyleSheet("background-image: url(:/icon/main/res/bk3.jpg);");
    ui->pushButton->setStyleSheet("border:0px groove gray;border-radius:10px;padding:2px 4px;");

    QVBoxLayout *pLayout = new QVBoxLayout(this);

    pLayout->addWidget(ui->lcdNumber);
    pLayout->addWidget(ui->pushButton);

    pLayout->setAlignment(ui->lcdNumber,Qt::AlignCenter);
    pLayout->setAlignment(ui->pushButton,Qt::AlignCenter);

    this->setLayout(pLayout);
}

time2restDlg::~time2restDlg()
{
    delete ui;
}

void time2restDlg::on_pushButton_clicked()
{
    close();
}

void time2restDlg::keyPressEvent(QKeyEvent* event){
    //printf("\nkey event in board: %i", event->key());
}
