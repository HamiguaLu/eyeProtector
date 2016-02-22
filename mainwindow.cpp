

#include <QSettings>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->m_lockTime->setValidator(new QIntValidator(1, 600, this));
    ui->m_saveBtn->setEnabled(false);

    //setStyleSheet("background-color:grey;");

    QSettings settings("eyeProtector.ini", QSettings::IniFormat);
    int xPos = settings.value("xPos", 200).toInt() - 100;
    int yPos = settings.value("yPos",300).toInt() - 250;

    if (xPos < 0)
    {
        xPos = 0;
    }

    if (yPos < 0)
    {
        yPos = 0;
    }

   move(xPos,yPos);

    loadSettings();

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
    emit settingsChanged();
    close();
}

void MainWindow::on_m_lockTime_textChanged(const QString &/*arg1*/)
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
