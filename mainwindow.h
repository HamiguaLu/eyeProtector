#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}


class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_m_saveBtn_clicked();

private:
    Ui::MainWindow *ui;

private slots:
   void onTimerEvent();
   void onTimerCounterEvent();
   void on_m_lockTime_textChanged(const QString &arg1);

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    QAction *newAct;

private slots:
    void newActSlot();

private:
    void loadSettings();
    void saveSettings();
    void startMonitor();
    QTimer *m_timer;
    QTimer *m_timerCounter;

    int m_iCounter;
};

#endif // MAINWINDOW_H
