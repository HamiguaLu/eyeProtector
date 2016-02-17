
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

    m_timer = new QTimer();
    m_timerCounter = new QTimer();

    m_iCounter = 0;
     startMonitor();
}

QRestTimeCounter::~QRestTimeCounter()
{
    m_timer->stop();
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


void QRestTimeCounter::onTimerEvent()
{
    emit time2restEvt();

    //startMonitor();
}


void QRestTimeCounter::onTimerCounterEvent()
{
    --m_iCounter;
    QString info = QString("%1 : %2 ").arg(m_iCounter / 60).arg(m_iCounter % 60);
     ui->label->setText(info);
}


void QRestTimeCounter::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(exitAct);
    menu.addAction(showMainUiAct);

    menu.exec(event->globalPos());
}


void QRestTimeCounter::startMonitor()
{
    m_timer->stop();
     connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimerEvent()));

    QSettings settings("eyeProtector.ini", QSettings::IniFormat);
     int timeout = settings.value("locktime",60).toInt();
     m_timer->start(timeout * 60* 1000);

    m_iCounter = timeout * 60;
    m_timerCounter->stop();
    connect(m_timerCounter,SIGNAL(timeout()),this,SLOT(onTimerCounterEvent()));
    m_timerCounter->start( 1000);

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




