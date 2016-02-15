


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QMessageBox>

#include <X11/Xlib.h>
extern void x11_window_set_on_top ( Window xid);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->m_lockTime->setValidator(new QIntValidator(1, 600, this));

    ui->m_saveBtn->setEnabled(false);

    QRestTimeCounter *m_restInfoDlg = new QRestTimeCounter();
    x11_window_set_on_top(m_restInfoDlg->winId());
     m_restInfoDlg->setWindowFlags(Qt::FramelessWindowHint);
    m_restInfoDlg->show();

    connect(m_restInfoDlg,SIGNAL(exitEvt()),this,SLOT(onExitEvt()) );
    connect(m_restInfoDlg,SIGNAL(showMainUIEvt()),this,SLOT(onShowMainUiEvt()) );
    connect(m_restInfoDlg,SIGNAL(time2restEvt()),this,SLOT(onTime2RestEvt()) );

    loadSettings();


}


void MainWindow::onExitEvt()
{
    close();
    QApplication::quit();
}


void MainWindow::onShowMainUiEvt()
{
    this->show();
}

void MainWindow::onTime2RestEvt()
{
}


MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::loadSettings()
{
    QSettings settings("eyeProtector.ini", QSettings::IniFormat);
    ui->m_lockTime->setText(settings.value("locktime",60).toString());
    ui->m_cbAutoStart->setChecked(settings.value("autostart",true).toBool());
}


void MainWindow::saveSettings()
{

    QSettings settings("eyeProtector.ini", QSettings::IniFormat);
    settings.setValue("locktime", ui->m_lockTime->text().toInt());
    settings.setValue("autostart", ui->m_cbAutoStart->isChecked());

}


void MainWindow::on_m_saveBtn_clicked()
{
    saveSettings();

    hide();
}

void MainWindow::on_m_lockTime_textChanged(const QString &arg1)
{
    if  (ui->m_lockTime->text().length() < 1)
    {
        return;
    }

    QSettings settings("eyeProtector.ini", QSettings::IniFormat);
     if (settings.value("locktime",60).toString() != ui->m_lockTime->text())
     {
       ui->m_saveBtn->setEnabled(true);
    }
     else
     {
         ui->m_saveBtn->setEnabled(false);
     }
}
