#include "typetreewidget.h"
#include "qmenu.h"

TypeTreeWidget::TypeTreeWidget(QWidget *parent) : QTreeWidget{parent}
{
    this->CreateContextMenus();

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenu(QPoint)));
}

TypeTreeWidget::~TypeTreeWidget()
{
    if(variantContextMenu != nullptr)
        delete variantContextMenu;
    if(typeContextMenu != nullptr)
        delete typeContextMenu;
}

void TypeTreeWidget::CreateContextMenus()
{
    //Types tree

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->typeContextMenu = new QMenu(this);
    this->variantContextMenu = new QMenu(this);

    QAction* renameAction = new QAction("Rename", this->typeContextMenu);
    this->typeContextMenu->addAction(renameAction);
    connect(renameAction, SIGNAL(triggered(bool)), this, SLOT(renameType()));

    QAction* deleteAction = new QAction("Delete", this);
    this->typeContextMenu->addAction(deleteAction);
    this->variantContextMenu->addAction(deleteAction);
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteTreeItem()));

    this->typeContextMenu->addSeparator();

    QAction* AddVariantAction = new QAction("Add new variant", this->typeContextMenu);
    this->typeContextMenu->addAction(AddVariantAction);
    connect(AddVariantAction, SIGNAL(triggered(bool)), this, SLOT(addNewVariant()));
}

void TypeTreeWidget::renameType()
{
    this->editItem(this->selectedItems()[0], 0);
    //TODO: disallow having the same names, as they are crucial to identify types
}
void TypeTreeWidget::deleteTreeItem()
{
    delete this->selectedItems()[0];
    this->typeContextMenu->hide();
}
void TypeTreeWidget::addNewVariant()
{
    int number = this->selectedItems()[0]->childCount() + 1;
    QString name = QString("Variant ") + QString::number(number);
    bool originalName = true;
    do
    {
        originalName = true;
        for(int i =0; i< this->selectedItems()[0]->childCount(); i++)
        {
            if(this->selectedItems()[0]->child(i)->text(0) == name)
            {
                name = QString("Variant ") + QString::number(++number);
                originalName = false;
                break;
            }
        }
    }
    while(!originalName);
    QTreeWidgetItem* newVariant = new QTreeWidgetItem(this->selectedItems()[0], QStringList(name));
    this->selectedItems()[0]->addChild(newVariant);
}

void TypeTreeWidget::onContextMenu(const QPoint &point)
{
    auto item = this->itemAt(point);
    if(item == nullptr) return;
    if(item->parent() != nullptr) //Variant item
    {
        this->variantContextMenu->exec(this->viewport()->mapToGlobal(point));
    }
    else //Type item
    {
        this->typeContextMenu->exec(this->viewport()->mapToGlobal(point));
    }
}


void TypeTreeWidget::addNewType()
{
    int number = this->topLevelItemCount() + 1;
    QString name = QString("Type ") + QString::number(number);
    bool originalName;
    do
    {
        originalName = true;
        if(this->findItems(name, Qt::MatchFlag::MatchExactly).size() != 0)
        {
            //The name already exists
            QString name = QString("Type ") + QString::number(++number);
            originalName = false;
        }
    }
    while(!originalName);

    QTreeWidgetItem* newType = new QTreeWidgetItem(this, QStringList(name));
    this->insertTopLevelItem(this->topLevelItemCount(), newType);

}

void TypeTreeWidget::addNewType(QString name)
{
    if(this->findItems(name, Qt::MatchFlag::MatchExactly).size() != 0)
    {
        return; //The name already exists
        //TODO: add some toopip that the name isn't avaliable. Delegade overrive might be needed
    }

    QTreeWidgetItem* newType = new QTreeWidgetItem(this, QStringList(name));
    this->insertTopLevelItem(this->topLevelItemCount(), newType);
}
