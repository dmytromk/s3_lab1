#include "mainwindow.h"
#include "ui_mainwindow.h"

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

