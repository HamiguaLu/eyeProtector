
#include <QtWidgets>
#include "qresttimecounter.h"
#include "ui_qresttimecounter.h"
#include "mainwindow.h"
#include "time2restdlg.h"


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
    connect(showMainUiAct, SIGNAL(triggered()), this, SLOT(onSetting()));

    setStyleSheet("background-color:#ccff99;");

    m_timerPerSec = new QTimer();

    m_iCounter = 0;
     startMonitor();

     ui->lcdNumber->resize(width(),height());

     QSettings settings("eyeProtector.ini", QSettings::IniFormat);
     int xPos = settings.value("xPos",QApplication::desktop()->width() - 200).toInt();
     int yPos = settings.value("yPos",QApplication::desktop()->height() - 200).toInt();

    move(xPos,yPos);

}

QRestTimeCounter::~QRestTimeCounter()
{
    m_timerPerSec->stop();
    delete ui;
}


void QRestTimeCounter::onExit()
{
    close();
    QApplication::quit();
}


void QRestTimeCounter::onSetting()
{
    MainWindow *w = new MainWindow();
    w->show();

    connect(w,SIGNAL(settingsChanged()),this,SLOT(onStartMonitor()));
}


#include <X11/Xlib.h>
extern void x11_window_set_on_top ( Window xid);

void QRestTimeCounter::onTimerCounterEvent()
{
    --m_iCounter;
    if (m_iCounter < 0)
    {
        m_timerPerSec->stop();

        time2restDlg *dlg = new time2restDlg();
        dlg->setWindowFlags(Qt::FramelessWindowHint);
        x11_window_set_on_top(dlg->winId());
        dlg->showFullScreen();
        connect(dlg,SIGNAL(restDlgClosed()),this,SLOT(onStartMonitor()));

        return;
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
        QPoint pos = event->globalPos() - m_dragPosition;
        move(pos.x(),pos.y());

        QSettings settings("eyeProtector.ini", QSettings::IniFormat);
        settings.setValue("xPos", pos.x());
        settings.setValue("yPos", pos.y());
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

void QRestTimeCounter::onStartMonitor()
{
    startMonitor();
}



