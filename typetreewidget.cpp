#include "typetreewidget.h"
#include "qmenu.h"
#include "QToolTip"
#include "typeTreeItem.h"
#include "variantTreeItem.h"

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
    std::vector<Alg::Type*> vec;
    for(int i=0; i< this->topLevelItemCount(); i++)
    {
        //Types
        TypeTreeItem* treeType = (TypeTreeItem*)this->topLevelItem(i);
        //treeType->text(0); <- typeName

        for(int j = 0; j < treeType->childCount(); j++)
        {
            //Variants
            VariantTreeItem* treeVariant = (VariantTreeItem*) treeType->child(i);

        }
    }
}

void TypeTreeWidget::CreateContextMenus()
{
    //TODO: memory management (new -> delete)

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->typeContextMenu = new QMenu(this);
    this->variantContextMenu = new QMenu(this);

    //Type actions
    QAction* renameTypeAction = new QAction("Rename", this->typeContextMenu);
    this->typeContextMenu->addAction(renameTypeAction);
    connect(renameTypeAction, SIGNAL(triggered(bool)), this, SLOT(renameType()));

    QAction* deleteTypeAction = new QAction("Delete", this->typeContextMenu);
    this->typeContextMenu->addAction(deleteTypeAction);
    connect(deleteTypeAction, SIGNAL(triggered(bool)), this, SLOT(deleteTreeType()));

    this->typeContextMenu->addSeparator();

    QAction* AddVariantAction = new QAction("Add new variant", this->typeContextMenu);
    this->typeContextMenu->addAction(AddVariantAction);
    connect(AddVariantAction, SIGNAL(triggered(bool)), this, SLOT(addNewVariant()));



    //Variant actions
    QAction* deleteVariantAction = new QAction("Delete", this->variantContextMenu);
    this->variantContextMenu->addAction(deleteVariantAction);
    connect(deleteVariantAction, SIGNAL(triggered(bool)), this, SLOT(deleteTreeVariant()));

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

void TypeTreeWidget::deleteTreeType()
{
    if(this->selectedItems()[0]->parent() != nullptr)
        delete this->selectedItems()[0]->parent();
    else
        delete this->selectedItems()[0];
    this->typeContextMenu->hide();
}

void TypeTreeWidget::deleteTreeVariant()
{
    if(this->selectedItems()[0]->parent()->childCount() < 2)
        return; // Cannot delete the only existing variant of a type
    //TODO: ^^^ Add maybe some tooltip?
    delete this->selectedItems()[0];
    this->typeContextMenu->hide();
}

void TypeTreeWidget::addNewVariant()
{
    QTreeWidgetItem* parentItem;
    if(selectedItems()[0]->parent() != nullptr)
        parentItem = selectedItems()[0]->parent();
    else
        parentItem = selectedItems()[0];

    int number = parentItem->childCount() + 1;
    QString name = QString("Variant ") + QString::number(number);
    bool originalName = true;
    do
    {
        originalName = true;
        for(int i =0; i< parentItem->childCount(); i++)
        {
            if(parentItem->child(i)->text(0) == name)
            {
                name = QString("Variant ") + QString::number(++number);
                originalName = false;
                break;
            }
        }
    }
    while(!originalName);
    VariantTreeItem* newVariant = new VariantTreeItem((TypeTreeItem*) parentItem, QStringList(name));
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

        QTreeWidgetItem* selected;

        if(this->selectedItems()[0]->parent() == nullptr) //Clicked on type
        {
            this->selectedItems()[0]->setExpanded(true);
            selected = this->selectedItems()[0]->child(0);
        }
        else //Clicked on variant
        {
            selected = this->selectedItems()[0];
        }

        this->lastSelected = (VariantTreeItem*) selected;
        this->setCurrentItem(selected);
        Alg::Variant* variant = ((VariantTreeItem*) selected)->variant();
        emit variantChanged(variant);

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

    TypeTreeItem* newType = new TypeTreeItem(this, QStringList(name));
    newType->setFlags(newType->flags() | Qt::ItemIsEditable);
    this->insertTopLevelItem(this->topLevelItemCount(), newType);


    //Add inifial variant
    VariantTreeItem* newVariant = new VariantTreeItem(newType, QStringList("Variant1"));
    newType->addChild(newVariant);

}

void TypeTreeWidget::addNewType(QString name)
{
    if(this->findItems(name, Qt::MatchFlag::MatchExactly).size() != 0)
    {
        //The name already exists
        //TODO: add some toopip that the name isn't avaliable.
        this->addNewType();
        return;
    }

    TypeTreeItem* newType = new TypeTreeItem(this, QStringList(name));
    this->insertTopLevelItem(this->topLevelItemCount(), newType);

    //Add inifial variant
    VariantTreeItem* newVariant = new VariantTreeItem(newType, QStringList("Variant1"));
    newType->addChild(newVariant);
}
