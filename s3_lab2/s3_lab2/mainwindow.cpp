#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    probSetWindow = new ProbabilitySetWindow();
    connect(probSetWindow, &ProbabilitySetWindow::mainMenuWindow,
            this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_probabilitySetButton_clicked()
{
    probSetWindow->show();
    this->close();
}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

