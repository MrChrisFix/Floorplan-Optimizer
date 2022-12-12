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

    connect(ui->addRequirementButton, SIGNAL(clicked(bool)), this, SLOT(onRequirementAdd()));
    connect(ui->typesTree, SIGNAL(variantChanged(Alg::Variant*)), ui->typeRequirementsTree, SLOT(onChangedType(Alg::Variant*)));

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

void MainWindow::onRequirementAdd()
{
    //Requirements tree
    this->ui->typeRequirementsTree->addRequirement(ui->DirComboBox->currentText(), ui->TypeComboBox->currentText());

    //Saving it in types
    QTreeWidgetItem* current = this->ui->typesTree->currentItem();
    if(current->parent() != nullptr)
        current = current->parent();

    Alg::Type* type = nullptr;
    char side = ui->DirComboBox->currentText().toStdString()[0];
    for(int i=0; i< ui->typesTree->topLevelItemCount(); i++)
    {
        if(((TypeTreeItem*) ui->typesTree->topLevelItem(i))->getType()->GetName() == ui->TypeComboBox->currentText().toStdString())
        {
            type = ((TypeTreeItem*) ui->typesTree->topLevelItem(i))->getType();
            break;
        }
    }
    if(type == nullptr)
        throw; //shouldn't occure

    ((TypeTreeItem*)current)->getType()->AddRequirement(side, type, true);
}
