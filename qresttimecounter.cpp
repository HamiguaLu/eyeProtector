
#include <QtWidgets>
#include "qresttimecounter.h"
#include "ui_qresttimecounter.h"

QRestTimeCounter::QRestTimeCounter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRestTimeCounter)
{
    ui->setupUi(this);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Exit eyeProtector"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(onExit()));

    showMainUiAct = new QAction(tr("&Settings"), this);
    showMainUiAct->setStatusTip(tr("Show main window"));
    connect(showMainUiAct, SIGNAL(triggered()), this, SLOT(onShowMainUi()));

    m_timerPerSec = new QTimer();

    m_iCounter = 0;
     startMonitor();

     ui->lcdNumber->resize(width(),height());
}

QRestTimeCounter::~QRestTimeCounter()
{
    m_timerPerSec->stop();
    delete ui;
}


void QRestTimeCounter::onExit()
{
    emit exitEvt();
}


void QRestTimeCounter::onShowMainUi()
{
    emit showMainUIEvt();
}


void QRestTimeCounter::onTimerCounterEvent()
{
    --m_iCounter;
    if (m_iCounter < 0)
    {
        m_timerPerSec->stop();
        emit time2restEvt();
        return;
    }

    QString info = "";
    if (m_iCounter > 3600)
    {
        info = QString("%1:%2:%3").arg(m_iCounter / 3600).arg( (m_iCounter % 3600)/ 60).arg(m_iCounter % 60);
    }
    else
    {
        info = QString("%1:%2 ").arg(m_iCounter / 60).arg(m_iCounter % 60);
    }

     ui->lcdNumber->display(info);
}


void QRestTimeCounter::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    menu.addAction(showMainUiAct);
    menu.addSeparator();
    menu.addAction(exitAct);

    menu.exec(event->globalPos());
}


void QRestTimeCounter::startMonitor()
{
    m_timerPerSec->stop();
    connect(m_timerPerSec,SIGNAL(timeout()),this,SLOT(onTimerCounterEvent()));

    QSettings settings("eyeProtector.ini", QSettings::IniFormat);
     int timeout = settings.value("locktime",60).toInt();
     m_iCounter = timeout * 60;

     m_timerPerSec->start(1000);

}


void QRestTimeCounter::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}
void QRestTimeCounter::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}


void QRestTimeCounter::keyPressEvent(QKeyEvent* /*event*/){

}



