#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "XML_Management/XMLFileManager.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Floorplan Optimizer");
    this->resultDialog = new ResultDialog(this);
    this->optionsDialog = new OptOptionsDialog(this);

    this->setupTheWindow();
    this->makeConnections();
}

MainWindow::~MainWindow()
{
    delete this->resultDialog;
    delete this->optionsDialog;
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
    connect(ui->typesTree, SIGNAL(variantChanged(FPA::Variant*)), ui->renderArea, SLOT(onVariantChange(FPA::Variant*)));
    connect(ui->typesTree, SIGNAL(variantChanged(FPA::Variant*)), this, SLOT(ChangeTypeComboBox(FPA::Variant*)));

    connect(ui->addRequirementButton, SIGNAL(clicked(bool)), this, SLOT(onRequirementAdd()));
    connect(ui->typeRequirementsTree, SIGNAL(RemoveRequiremntPartner(QString)), this, SLOT(onRequirementRemove(QString)));
    connect(ui->typesTree, SIGNAL(variantChanged(FPA::Variant*)), ui->typeRequirementsTree, SLOT(onChangedType(FPA::Variant*)));
    connect(ui->typesTree, SIGNAL(TypeDeleted()), this, SLOT(onTypeDelete()));

    connect(this->optionsDialog, SIGNAL(accepted()), this, SLOT(FindOptimal()));

    //Menubar actions
    connect(ui->actionAdd_new_type, SIGNAL(triggered(bool)), ui->typesTree, SLOT(addNewType()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->actionImport, SIGNAL(triggered(bool)), this, SLOT(importXML()));
    connect(ui->actionExport, SIGNAL(triggered(bool)), this, SLOT(exportXML()));
    connect(ui->actionStart_optimization, SIGNAL(triggered(bool)), this, SLOT(onStartOptimization()));
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(onNewAction()));
}

void MainWindow::onNewAction()
{
    ui->typesTree->clear();
    ui->typeRequirementsTree->clear();
    ui->TypeComboBox->clear();
}

void MainWindow::ChangeTypeComboBox(FPA::Variant* var)
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
    if(ui->TypeComboBox->count() == 0)
        return;

    //Requirements tree
    bool sucessful;
    sucessful = this->ui->typeRequirementsTree->addRequirement(ui->DirComboBox->currentText(), ui->TypeComboBox->currentText());

    if(!sucessful) return;

    //Saving it in types
    QTreeWidgetItem* current = this->ui->typesTree->currentItem();
    if(current == nullptr) return;

    if(current->parent() != nullptr)
        current = current->parent();

    FPA::Type* type = nullptr;
    char side = ui->DirComboBox->currentText().toStdString()[0];
    for(int i=0; i< ui->typesTree->topLevelItemCount(); i++)
    {
        if(( (TypeTreeItem*) ui->typesTree->topLevelItem(i) )->getType()->GetName() == ui->TypeComboBox->currentText().toStdString())
        {
            type = ((TypeTreeItem*) ui->typesTree->topLevelItem(i))->getType();
            break;
        }
    }
    if(type == nullptr)
        throw; //shouldn't occure

    ((TypeTreeItem*)current)->getType()->AddRequirement(side, type, true);
}

void MainWindow::onRequirementRemove(QString typeName)
{
    QTreeWidgetItem* current = this->ui->typesTree->currentItem();
    if(current == nullptr) return;

    if(current->parent() != nullptr)
        current = current->parent();

    FPA::Type* type = nullptr;
    for(int i=0; i< ui->typesTree->topLevelItemCount(); i++)
    {
        if(( (TypeTreeItem*) ui->typesTree->topLevelItem(i) )->getType()->GetName() == typeName.toStdString())
        {
            type = ((TypeTreeItem*) ui->typesTree->topLevelItem(i))->getType();
            break;
        }
    }
    if(type == nullptr)
        throw; //shouldn't occure

    type->RemoveRequirement(((TypeTreeItem*)current)->getType(), true);
}

void MainWindow::onStartOptimization()
{
    auto types = ui->typesTree->GetTypeVector();

    if(types.size() == 0)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("No types");
        msgbox.setIcon(QMessageBox::Icon::Information);
        msgbox.setText(QString("There are no types to optimize"));
        msgbox.exec();
        return;
    }

    this->optionsDialog->open();
}

void MainWindow::FindOptimal()
{
    bool multiThread = this->optionsDialog->useMultithread();
    unsigned int threads = this->optionsDialog->getThreadNum();

    auto types = ui->typesTree->GetTypeVector();

    FPA::AlgorithmManager manager;
    manager.setTypes(types);
    auto result = manager.StartCalculations(threads, multiThread);

    this->resultDialog->setResults(result);
    this->resultDialog->open();
}

void MainWindow::importXML()
{
    //QFileDialog
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select XML"), "/", tr("XML Files (*.xml)"));
    if(filePath.isEmpty()) return;
    XMLFileManager XMLManager;

    std::vector<FPA::Type*> types;

    try {
        types = XMLManager.ReadFromXML(filePath.toStdString());
    }
    catch(const char* message)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("Error");
        msgbox.setIcon(QMessageBox::Icon::Critical);
        msgbox.setText(QString(message));
        msgbox.exec();
    }
    catch (...)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("Error");
        msgbox.setIcon(QMessageBox::Icon::Critical);
        msgbox.setText(QString("Something went wrong!"));
        msgbox.exec();
    }

    ui->typesTree->InsertTypeVector(types);
}

void MainWindow::exportXML()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save to XML"), "/", tr("XML Files (*.xml)"));
    if(filePath.isEmpty()) return;
    auto types = ui->typesTree->GetTypeVector();
    XMLFileManager XMLManager;
    XMLManager.SaveToXML(types, filePath.toStdString());
}

void MainWindow::onTypeDelete()
{
    ui->TypeComboBox->clear();
    ui->typeRequirementsTree->clear();
}
