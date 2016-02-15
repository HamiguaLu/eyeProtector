#ifndef QRESTTIMECOUNTER_H
#define QRESTTIMECOUNTER_H

#include <QDialog>

namespace Ui {
class QRestTimeCounter;
}

class QAction;
class QActionGroup;
class QLabel;
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
    QTimer *m_timer;
    QTimer *m_timerCounter;

    int m_iCounter;

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    QAction *exitAct;
    QAction *showMainUiAct;

private slots:
    void onExit();
    void onShowMainUi();
    void onTimerEvent();
    void onTimerCounterEvent();

signals:
     void showMainUIEvt();
     void exitEvt();
};

#endif // QRESTTIMECOUNTER_H
