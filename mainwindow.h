#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>


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
    void on_m_lockTime_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

private:
    void loadSettings();
    void saveSettings();

signals:
     void settingsChanged();

};

#endif // MAINWINDOW_H
