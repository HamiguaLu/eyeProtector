#ifndef QRESTTIMECOUNTER_H
#define QRESTTIMECOUNTER_H

#include <QDialog>

namespace Ui {
class QRestTimeCounter;
}

class QAction;
class QMenu;

class QRestTimeCounter : public QDialog
{
    Q_OBJECT

public:
    explicit QRestTimeCounter(QWidget *parent = 0);
    ~QRestTimeCounter();

private:
    Ui::QRestTimeCounter *ui;
    void startMonitor();
    QTimer *m_timerPerSec;

    int m_iCounter;

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    QAction *exitAct;
    QAction *showMainUiAct;

private slots:
    void onStartMonitor();
    void onTimerCounterEvent();
    void onExit();
    void onSetting();


protected:
     QPoint m_dragPosition;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    virtual void  keyPressEvent(QKeyEvent *event);
};

#endif // QRESTTIMECOUNTER_H
