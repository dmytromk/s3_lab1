#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <random>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::get_probabilities_sum()
{
    ui->eventTable->blockSignals(true);

    double result = 0;
    int cur_row = ui->eventTable->rowCount();

    for(int i = 0; i < cur_row; ++i)
        result += ui->eventTable->item(i, 1)->text().toDouble();

    ui->eventTable->blockSignals(false);

    return result;
}

int MainWindow::get_event_by_probability(double probability)
{
    ui->eventTable->blockSignals(true);

    double sum = this->get_probabilities_sum();
    double cur_prob = 0;

    int cur_row = ui->eventTable->rowCount();

    for(int i = 0; i < cur_row; ++i)
    {
        double to_compare = ui->eventTable->item(i, 1)->text().toDouble();
        if(to_compare/sum + cur_prob >= probability)
            return ui->eventTable->item(i, 0)->text().toInt();
        else cur_prob += to_compare;
    }


    ui->eventTable->blockSignals(false);

    return -1;
}

void MainWindow::on_addButton_clicked()
{
    ui->eventTable->blockSignals(true);

    int event = ui->eventInpuBox->value();
    double probability = ui->probabilityInputBox->value();
    int cur_row = ui->eventTable->rowCount();

    for(int i = 0; i < cur_row; ++i)
    {
        if(ui->eventTable->item(i, 0)->text() == QString::number(event))
        {
            //we have found the same event
            double changed = ui->eventTable->item(i, 1)->text().toDouble() + probability;
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setData(Qt::EditRole, changed);
            ui->eventTable->setItem(i, 1, item);
            return;
        }
    }


    ui->eventTable->insertRow(cur_row);

    QTableWidgetItem* itemEvent = new QTableWidgetItem;
    itemEvent->setData(Qt::EditRole, event);
    ui->eventTable->setItem(cur_row, 0, itemEvent);

    QTableWidgetItem* itemProbability = new QTableWidgetItem;
    itemProbability->setData(Qt::EditRole, probability);
    ui->eventTable->setItem(cur_row, 1, itemProbability);

    ui->eventTable->sortItems(0, Qt::AscendingOrder);

    ui->eventTable->blockSignals(false);
}

void MainWindow::on_clearButton_clicked()
{
    ui->eventTable->setRowCount(0);
    ui->eventTable->clearContents();
}


void MainWindow::on_eventTable_cellChanged(int row, int column)
{
    if(column!=0)
        return;

    ui->eventTable->sortItems(0, Qt::AscendingOrder);
}


void MainWindow::on_simulateButton_clicked()
{
    const int RAND_CONST = 1;
    const int COEFICIENT = 5555;

    ui->simulationTable->blockSignals(true);

    int stepsAmount = ui->stepsAmountBox->value();
    int seed = ui->seedBox->value();

    std::default_random_engine generator{static_cast<unsigned int>((RAND_CONST+seed)*COEFICIENT)};
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    srand(RAND_CONST+seed);

    ui->simulationTable->setColumnCount(0);
    ui->simulationTable->clearContents();

    for(int i = 1; i <= stepsAmount; i++)
    {
        double probability = distribution(generator);
        int event = this->get_event_by_probability(probability);

        ui->simulationTable->insertColumn(i-1);

        QTableWidgetItem* itemStep = new QTableWidgetItem;
        itemStep->setTextAlignment(Qt::AlignCenter);
        itemStep->setData(Qt::EditRole, i);
        ui->simulationTable->setItem(0, i-1, itemStep);

        QTableWidgetItem* itemResult = new QTableWidgetItem;
        itemResult->setTextAlignment(Qt::AlignCenter);
        itemResult->setData(Qt::EditRole, event);
        ui->simulationTable->setItem(1, i-1, itemResult);
    }

    ui->simulationTable->blockSignals(false);
}

