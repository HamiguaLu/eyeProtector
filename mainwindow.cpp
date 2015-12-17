#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->m_lockTime->setValidator(new QIntValidator(1, 600, this));
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
}
