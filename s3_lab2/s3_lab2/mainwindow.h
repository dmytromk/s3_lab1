#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum events_set_columns
    {
        EVENT,
        NAME,
        PROBABILITY
    };

    enum simulation_columns
    {
        STEP,
        RESULT
    };


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    double get_probabilities_sum();

    int get_event_by_probability(double probability);

    void on_addButton_clicked();

    void on_clearButton_clicked();

    void on_simulateButton_clicked();

    void on_randomizeSeedButton_clicked();

    void on_exportCSVButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
