#ifndef TIME2RESTDLG_H
#define TIME2RESTDLG_H

#include <QDialog>

namespace Ui {
class time2restDlg;
}

class time2restDlg : public QDialog
{
    Q_OBJECT

public:
    explicit time2restDlg(QWidget *parent = 0);
    ~time2restDlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::time2restDlg *ui;

protected:
    virtual void  keyPressEvent(QKeyEvent *event);
};

#endif // TIME2RESTDLG_H
