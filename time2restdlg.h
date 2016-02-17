#ifndef TIME2RESTDLG_H
#define TIME2RESTDLG_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class time2restDlg;
}

#define EP_MAX_REST_TIME    (2*60)   // 2 minutes

class time2restDlg : public QDialog
{
    Q_OBJECT

public:
    explicit time2restDlg(QWidget *parent = 0);
    ~time2restDlg();

private slots:
    void on_pushButton_clicked();
    void onTimerCounterEvent();

private:
    Ui::time2restDlg *ui;

private:
    QTimer *m_timerPerSec;
    int m_iCounter;

protected:
    virtual void  keyPressEvent(QKeyEvent *event);

signals:
     void restDlgClosed();
};

#endif // TIME2RESTDLG_H
