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

    int bkIndex = rand() % 6;
    if (bkIndex == 0){
        bkIndex = 1;
    }

    QString css = QString("background-image: url(:/icon/main/res/bk%1.jpg)").arg(bkIndex);
    setStyleSheet(css);
    ui->pushButton->setStyleSheet("border:0px groove gray;border-radius:10px;padding:2px 4px;");

    QVBoxLayout *pLayout = new QVBoxLayout(this);

    pLayout->addWidget(ui->lcdNumber);
    pLayout->addWidget(ui->pushButton);

    pLayout->setAlignment(ui->lcdNumber,Qt::AlignCenter);
    pLayout->setAlignment(ui->pushButton,Qt::AlignCenter);

    this->setLayout(pLayout);


    m_iCounter = EP_MAX_REST_TIME;
    m_timerPerSec = new QTimer();
    connect(m_timerPerSec,SIGNAL(timeout()),this,SLOT(onTimerCounterEvent()));
    m_timerPerSec->start(1000);

    //ui->pushButton->setEnabled(false);
    onTimerCounterEvent();
}

time2restDlg::~time2restDlg()
{
    delete ui;
}

void time2restDlg::on_pushButton_clicked()
{
    emit restDlgClosed();
    close();
}

void time2restDlg::keyPressEvent(QKeyEvent* /*event*/){

}

void time2restDlg::onTimerCounterEvent()
{
    --m_iCounter;
    if (m_iCounter < 0)
    {
        m_timerPerSec->stop();
        emit restDlgClosed();
        close();
        return;
    }

    if (m_iCounter < EP_MAX_REST_TIME/2)
    {
        ui->pushButton->setEnabled(true);
    }

    QString info = "";
    if (m_iCounter > 3600)
    {
        info.sprintf("%02d:%02d:%02d",m_iCounter / 3600,(m_iCounter % 3600)/ 60,m_iCounter % 60);
    }
    else
    {
        info.sprintf("%02d:%02d",m_iCounter / 60, m_iCounter % 60);
    }

     ui->lcdNumber->display(info);
}


