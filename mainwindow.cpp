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
    connect(ui->typesTree, SIGNAL(variantChanged(Alg::Variant*)), ui->renderArea, SLOT(onVariantChange(Alg::Variant*)));
    connect(ui->typesTree, SIGNAL(variantChanged(Alg::Variant*)), this, SLOT(ChangeTypeComboBox(Alg::Variant*)));

    //Menubar actions
    connect(ui->actionAdd_new_type, SIGNAL(triggered(bool)), ui->typesTree, SLOT(addNewType()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));

    //TODO: import and export -> QFileDialog
}

void MainWindow::ChangeTypeComboBox(Alg::Variant* var)
{
    ui->TypeComboBox->clear();
    QString selTypeName = QString::fromStdString(var->GetType()->GetName());

    QStringList typeList;
    for(int i=0; i< ui->typesTree->topLevelItemCount(); i++)
    {
        if(ui->typesTree->topLevelItem(i)->text(0) != selTypeName)
            typeList.push_back(ui->typesTree->topLevelItem(i)->text(0));
    }

    ui->TypeComboBox->addItems(typeList);
}
