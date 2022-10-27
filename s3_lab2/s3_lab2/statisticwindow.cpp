#include "statisticwindow.h"
#include "ui_statisticwindow.h"

StatisticWindow::StatisticWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticWindow)
{
    ui->setupUi(this);
}

StatisticWindow::~StatisticWindow()
{
    delete ui;
}

void StatisticWindow::set_expected_value(const QString &expected_value)
{
    ui->expectedValueLabel->setText(expected_value);
}

void StatisticWindow::set_variance(const QString &variance)
{
    ui->varianceLabel->setText(variance);
}

void StatisticWindow::set_average_value(const QString &average_value)
{
    ui->averageValueLabel->setText(average_value);
}

