#include "typetreewidget.h"
#include "qmenu.h"
#include "QToolTip"
#include "qmessagebox.h"
#include "typeTreeItem.h"
#include "variantTreeItem.h"

TypeTreeWidget::TypeTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    this->CreateContextMenus();

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenu(QPoint)));
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(checkNewName(QTreeWidgetItem*)));
    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(SelectionChange()));
}

TypeTreeWidget::~TypeTreeWidget()
{
    if(variantContextMenu != nullptr)
    {
        for(auto action : variantContextMenu->actions())
            delete action;
        delete variantContextMenu;
        variantContextMenu = nullptr;
    }

    if(typeContextMenu != nullptr)
    {
        for(auto action : typeContextMenu->actions())
            delete action;
        delete typeContextMenu;
        typeContextMenu = nullptr;
    }
}

std::vector<FPA::Type*> TypeTreeWidget::GetTypeVector()
{
    std::vector<FPA::Type*> vec;
    for(int i=0; i< this->topLevelItemCount(); i++)
    {
        TypeTreeItem* treeType = (TypeTreeItem*)this->topLevelItem(i);
        vec.push_back(treeType->getType());
    }
    return vec;
}

void TypeTreeWidget::InsertTypeVector(std::vector<FPA::Type*> &types)
{
    this->clear();

    for(auto& type : types)
    {
        QString name = QString::fromStdString(type->GetName());
        TypeTreeItem* typeItem = new TypeTreeItem(this, QStringList(name));
        typeItem->setType(type);
        this->addTopLevelItem((QTreeWidgetItem*)typeItem);
        for(int i=0; i < type->GetVariants().size(); i++)
        {
            QString varName = QString("Varaint ") + QString::number(i+1);
            VariantTreeItem* varItem = new VariantTreeItem(typeItem, QStringList(varName));
            varItem->setVariant(type->GetVariants()[i]);
            typeItem->addChild(varItem);
        }
    }
}

void TypeTreeWidget::CreateContextMenus()
{
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
    TypeTreeItem* item;
    if(this->selectedItems()[0]->parent() != nullptr)
        item = (TypeTreeItem*) this->selectedItems()[0]->parent();
    else
        item = (TypeTreeItem*) this->selectedItems()[0];
    this->oldTypeNameHolder = item->text(0);
    this->editItem(item, 0);
}

void TypeTreeWidget::checkNewName(QTreeWidgetItem* changedItem)
{
    //Trimming name
    changedItem->setText(0, changedItem->text(0).trimmed());

    if(changedItem->text(0).size() == 0)
    {
        changedItem->setText(0, this->oldTypeNameHolder);
        return;
    }

    //Finding duplicates
    auto found = this->findItems(changedItem->text(0), Qt::MatchFlag::MatchExactly, 0);
    if(found.size() > 1)
    {
        changedItem->setText(0, this->oldTypeNameHolder);
        QMessageBox msgbox;
        msgbox.setWindowTitle("Information");
        msgbox.setIcon(QMessageBox::Icon::Information);
        msgbox.setText(QString("A type with this name already exists"));
        msgbox.exec();
        return;
    }

    ((TypeTreeItem*)changedItem)->getType()->setName(changedItem->text(0).toStdString());
}

void TypeTreeWidget::deleteTreeType()
{
    this->lastSelected = nullptr;

    if(this->selectedItems()[0]->parent() != nullptr)
        delete this->selectedItems()[0]->parent();
    else
        delete this->selectedItems()[0];
    this->typeContextMenu->hide();

    emit TypeDeleted();
}

void TypeTreeWidget::deleteTreeVariant()
{
    this->lastSelected = nullptr;

    if(this->selectedItems()[0]->parent()->childCount() < 2)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("Information");
        msgbox.setIcon(QMessageBox::Icon::Information);
        msgbox.setText(QString("Cannot remove the last variant. Each type must have at least 1 variant"));
        msgbox.exec();
        return; // Cannot delete the only existing variant of a type
    }
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
    parentItem->addChild(newVariant);
    ((TypeTreeItem*)parentItem)->getType()->AddVariant(newVariant->variant());
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
    if(this->selectedItems().size() == 0)
    {
        if(this->topLevelItemCount() == 0)
        {
            this->lastSelected = nullptr;
            return;
        }

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
        FPA::Variant* variant = ((VariantTreeItem*) selected)->variant();
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

    //Add initial variant
    VariantTreeItem* newVariant = new VariantTreeItem(newType, QStringList("Variant 1"));
    newType->addChild(newVariant);
    newType->getType()->AddVariant(newVariant->variant());
}
