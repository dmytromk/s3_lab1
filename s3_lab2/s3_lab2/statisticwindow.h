#ifndef STATISTICWINDOW_H
#define STATISTICWINDOW_H

#include <QWidget>

namespace Ui {
class StatisticWindow;
}

class StatisticWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticWindow(QWidget *parent = nullptr);
    ~StatisticWindow();
    void set_expected_value(const QString &expected_value);
    void set_variance(const QString &variance);
    void set_average_value(const QString &average_value);

private:
    Ui::StatisticWindow *ui;
};

#endif // STATISTICWINDOW_H
