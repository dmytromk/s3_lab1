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

    double get_event_by_probability(double probability);

    double get_moment(int power);

    double get_variance();

    double get_average_random_var();

    void on_addButton_clicked();

    void on_clearButton_clicked();

    void on_simulateButton_clicked();

    void on_randomizeSeedButton_clicked();

    void on_exportCSVButton_clicked();

    void on_statisticsButton_clicked();

    void on_deleteSelectedButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
