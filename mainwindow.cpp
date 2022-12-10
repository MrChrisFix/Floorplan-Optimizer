#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setupTheWindow();
    this->makeConnections();
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

void MainWindow::makeConnections()
{
    connect(ui->widthTextEdit, SIGNAL(textChanged(QString)), ui->renderArea, SLOT(setLength(QString)));
    connect(ui->heightTextEdit, SIGNAL(textChanged(QString)), ui->renderArea, SLOT(setHeight(QString)));
    connect(ui->actionAdd_new_type, SIGNAL(triggered(bool)), ui->typesTree, SLOT(addNewType()));
}
