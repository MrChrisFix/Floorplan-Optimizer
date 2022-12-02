#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setupTheWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTheWindow()
{
    ui->typesTree->setMaximumWidth(150);
    ui->typeRequirementsTree->setMaximumWidth(150);
}


