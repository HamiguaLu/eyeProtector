#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qresttimecounter.h"
#include "time2restdlg.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_m_saveBtn_clicked();
    void onExitEvt();
    void onShowMainUiEvt();
    void onTime2RestEvt();
private:
    Ui::MainWindow *ui;
    QRestTimeCounter *m_restInfoDlg;
    time2restDlg *m_lockDlg;

private slots:

   void on_m_lockTime_textChanged(const QString &arg1);



private:
    void loadSettings();
    void saveSettings();

};

#endif // MAINWINDOW_H
