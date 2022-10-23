#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "probabilitysetwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_probabilitySetButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
    ProbabilitySetWindow *probSetWindow;
};
#endif // MAINWINDOW_H
