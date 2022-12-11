#include "typetreewidget.h"
#include "qmenu.h"
#include "QToolTip"

#include <QDebug>

TypeTreeWidget::TypeTreeWidget(QWidget *parent) : QTreeWidget{parent}
{
    this->CreateContextMenus();

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenu(QPoint)));
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(checkNewName(QTreeWidgetItem*)));
    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(SelectionChange()));
}

TypeTreeWidget::~TypeTreeWidget()
{
    if(variantContextMenu != nullptr)
        delete variantContextMenu;
    if(typeContextMenu != nullptr)
        delete typeContextMenu;
}

void TypeTreeWidget::GetTypeVector()
{
    for(int i=0; i< this->topLevelItemCount(); i++)
    {
        //Types
        auto treeType = this->topLevelItem(i);
        //treeType->text(0); <- typeName

        for(int j = 0; j < treeType->childCount(); j++)
        {
            //Variants
            auto treeVariant = treeType->child(i);

            //Useless??
            //Unless the treeVariant would have the size inside
        }
    }
}

void TypeTreeWidget::CreateContextMenus()
{
    //Types tree

    //TODO: memory management (new -> delete)

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
    this->oldTypeNameHolder = this->selectedItems()[0]->text(0);
    this->editItem(this->selectedItems()[0], 0);
}

void TypeTreeWidget::checkNewName(QTreeWidgetItem* changedItem)
{
    //Trimming name
    changedItem->setText(0, changedItem->text(0).trimmed());

    //Finding duplicates
    for(int i=0; i< this->topLevelItemCount(); i++)
    {
        if(this->topLevelItem(i) == changedItem) continue;

        if(this->topLevelItem(i)->text(0) == changedItem->text(0))
        {
            changedItem->setText(0, this->oldTypeNameHolder);
        }
    }
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


void TypeTreeWidget::SelectionChange()
{
    //qInfo() << this->selectedItems().size();

    if(this->selectedItems().size() == 0)
    {
        if(this->lastSelected != nullptr)
            this->setCurrentItem(this->lastSelected);
    }
    else
    {
        this->selectedItems()[0]->setExpanded(true);
        //TODO: if type cheang selection to first variant
        if(this->selectedItems()[0]->parent() == nullptr)
            this->setCurrentItem(this->selectedItems()[0]->child(0));


        if(selectedItems()[0] == lastSelected)
        {
            emit variantChanged();
        }
        else
            this->lastSelected = this->selectedItems()[0];
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
            name = QString("Type ") + QString::number(++number);
            originalName = false;
        }
    }
    while(!originalName);

    QTreeWidgetItem* newType = new QTreeWidgetItem(this, QStringList(name));
    newType->setFlags(newType->flags() | Qt::ItemIsEditable);
    this->insertTopLevelItem(this->topLevelItemCount(), newType);


    //Add inifial variant
    QTreeWidgetItem* newVariant = new QTreeWidgetItem(newType, QStringList("Variant1"));
    newType->addChild(newVariant);

}

void TypeTreeWidget::addNewType(QString name)
{
    if(this->findItems(name, Qt::MatchFlag::MatchExactly).size() != 0)
    {
        //The name already exists
        //TODO: add some toopip that the name isn't avaliable. Delegade overrive might be needed
        this->addNewType();
        return;
    }

    QTreeWidgetItem* newType = new QTreeWidgetItem(this, QStringList(name));
    this->insertTopLevelItem(this->topLevelItemCount(), newType);

    //Add inifial variant
    QTreeWidgetItem* newVariant = new QTreeWidgetItem(newType, QStringList("Variant1"));
    newType->addChild(newVariant);
}
