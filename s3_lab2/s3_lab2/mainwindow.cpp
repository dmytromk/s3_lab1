#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"

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
    int probability_col = events_set_columns(PROBABILITY);

    ui->eventTable->blockSignals(true);

    double result = 0;
    int cur_row = ui->eventTable->rowCount();

    for(int i = 0; i < cur_row; ++i)
        result += ui->eventTable->item(i, probability_col)->text().toDouble();

    ui->eventTable->blockSignals(false);

    return result;
}

int MainWindow::get_event_by_probability(double probability)
{
    int event_col = events_set_columns(EVENT);
    int probability_col = events_set_columns(PROBABILITY);

    ui->eventTable->blockSignals(true);

    double sum = this->get_probabilities_sum();
    double cur_prob = 0;

    int cur_row = ui->eventTable->rowCount();

    for(int i = 0; i < cur_row; ++i)
    {
        double prob_to_compare = ui->eventTable->item(i, probability_col)->text().toDouble();
        if((prob_to_compare + cur_prob)/sum >= probability)
            return ui->eventTable->item(i, event_col)->text().toInt();
        else cur_prob += prob_to_compare;
    }

    ui->eventTable->blockSignals(false);

    return -1;
}

void MainWindow::on_addButton_clicked()
{
    ui->eventTable->setSortingEnabled(false);

    int event_col = events_set_columns(EVENT);
    int name_col = events_set_columns(NAME);
    int probability_col = events_set_columns(PROBABILITY);

    int event = ui->eventInpuBox->value();
    QString name = ui->eventNameLine->text();
    double probability = ui->probabilityInputBox->value();

    int cur_row = ui->eventTable->rowCount();

    for(int i = 0; i < cur_row; ++i)
    {
        if(ui->eventTable->item(i, EVENT)->text() == QString::number(event))
        {
            //we have found the same event
            double changed_probability = ui->eventTable->item(i, probability_col)->text().toDouble() + probability;
            QTableWidgetItem* itemNewEvent = new QTableWidgetItem;
            itemNewEvent->setData(Qt::EditRole, changed_probability);
            ui->eventTable->setItem(i, probability_col, itemNewEvent);

            QTableWidgetItem* itemNewName = new QTableWidgetItem;
            itemNewName->setData(Qt::EditRole, name);
            ui->eventTable->setItem(i, name_col, itemNewName);

            ui->eventTable->setSortingEnabled(true);

            return;
        }
    }


    ui->eventTable->insertRow(cur_row);

    QTableWidgetItem* itemEvent = new QTableWidgetItem;
    itemEvent->setData(Qt::EditRole, event);
    ui->eventTable->setItem(cur_row, event_col, itemEvent);

    QTableWidgetItem* itemName = new QTableWidgetItem;
    itemName->setData(Qt::EditRole, name);
    ui->eventTable->setItem(cur_row, name_col, itemName);

    QTableWidgetItem* itemProbability = new QTableWidgetItem;
    itemProbability->setData(Qt::EditRole, probability);
    ui->eventTable->setItem(cur_row, probability_col, itemProbability);

    ui->eventTable->setSortingEnabled(true);
}

void MainWindow::on_clearButton_clicked()
{
    ui->eventTable->setRowCount(0);
    ui->eventTable->clearContents();
}

void MainWindow::on_simulateButton_clicked()
{
    int step_col = simulation_columns(STEP);
    int result_col = simulation_columns(RESULT);

    const int RAND_CONST = 1;
    const int COEFICIENT = 5555;

    ui->simulationTable->blockSignals(true);

    int stepsAmount = ui->stepsAmountBox->value();
    int seed = ui->seedBox->value();

    std::default_random_engine generator{static_cast<unsigned int>((RAND_CONST+seed)*COEFICIENT)};
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    ui->simulationTable->setRowCount(0);
    ui->simulationTable->clearContents();

    for(int i = 1; i <= stepsAmount; i++)
    {
        double probability = distribution(generator);
        int event = this->get_event_by_probability(probability);

        ui->simulationTable->insertRow(i-1);

        QTableWidgetItem* itemStep = new QTableWidgetItem;
        itemStep->setTextAlignment(Qt::AlignCenter);
        itemStep->setData(Qt::EditRole, i);
        ui->simulationTable->setItem(i-1, step_col, itemStep);

        QTableWidgetItem* itemResult = new QTableWidgetItem;
        itemResult->setTextAlignment(Qt::AlignCenter);
        itemResult->setData(Qt::EditRole, event);
        ui->simulationTable->setItem(i-1, result_col, itemResult);
    }
}

void MainWindow::on_randomizeSeedButton_clicked()
{
    int seed = rand();
    ui->seedBox->setValue(seed/10);
}

void MainWindow::on_exportCSVButton_clicked()
{
    int step_col = simulation_columns(STEP);
    int result_col = simulation_columns(RESULT);

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QFile data(dir+"/simulation.csv");
    data.open(QFile::WriteOnly | QFile::Truncate |QIODevice::Append);
    QTextStream output(&data);

    int cur_row = ui->simulationTable->rowCount();

    output << "Step" << "," << "Result"<< '\n';
    for(int i=0;i<cur_row; i++) {
        output << ui->simulationTable->item(i, step_col)->text() << "," << ui->simulationTable->item(i, result_col)->text() << '\n';
    }
    data.close();
}

