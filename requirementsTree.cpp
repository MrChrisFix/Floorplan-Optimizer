#include "requirementsTree.h"
#include "Algorithm/Type.h"
#include "qmenu.h"

RequirementsTree::RequirementsTree(QWidget *parent) : QTreeWidget(parent)
{
    this->Up = new QTreeWidgetItem(this, QStringList("Up"));
    this->Left = new QTreeWidgetItem(this, QStringList("Left"));
    this->Down = new QTreeWidgetItem(this, QStringList("Down"));
    this->Right = new QTreeWidgetItem(this, QStringList("Right"));
    QList<QTreeWidgetItem*> list;
    list.append(Up);
    list.append(Left);
    list.append(Down);
    list.append(Right);
    this->addTopLevelItems(list);

    this->contextMenu = new QMenu();
    QAction* deleteAction = new QAction("Delete", this->contextMenu);
    this->contextMenu->addAction(deleteAction);
    //connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(RemoveRequirement(QTreeWidgetItem*)));

    this->currentType = nullptr;
}

RequirementsTree::~RequirementsTree()
{
    delete this->contextMenu;
    this->currentType = nullptr;
}

void RequirementsTree::onChangedType(Alg::Variant* newVariant)
{
    Alg::Type* type = newVariant->GetType();
    if(this->currentType == nullptr || this->currentType != type)
        this->currentType = type;
    else if(this->currentType == type)
        return; //optimation

    for(int i=0; i< this->topLevelItemCount(); i++)
        for(int j=0; j< this->topLevelItem(i)->childCount(); j++)
            delete this->topLevelItem(i)->child(j);


    for(Alg::Type* dir: type->up)
    {
        QTreeWidgetItem* newItem = new QTreeWidgetItem(this->Up);
        newItem->setText(0, QString::fromStdString(dir->GetName()));
        this->Up->addChild(newItem);
    }

    for(auto dir: type->left)
    {
        QTreeWidgetItem* newItem = new QTreeWidgetItem(this->Left);
        newItem->setText(0, QString::fromStdString(dir->GetName()));
        this->Left->addChild(newItem);
    }

    for(auto dir: type->down)
    {
        QTreeWidgetItem* newItem = new QTreeWidgetItem(this->Down);
        newItem->setText(0, QString::fromStdString(dir->GetName()));
        this->Down->addChild(newItem);
    }

    for(auto dir: type->right)
    {
        QTreeWidgetItem* newItem = new QTreeWidgetItem(this->Right);
        newItem->setText(0, QString::fromStdString(dir->GetName()));
        this->Right->addChild(newItem);
    }
}

bool RequirementsTree::addRequirement(QString direction, QString typeName)
{
    QTreeWidgetItem* dirItem = nullptr;

    //Check if the reqirement is already in the tree
    QTreeWidgetItem* item = this->isTypeAlreadyPresent(typeName);
    if(item != nullptr)
    {
        //If present, remove the old one and if dirrenet direction, place in new place
        if(item->parent()->text(0) != direction)
            this->RemoveRequirement(item);
        else
            return false; //nothing changed
    }

    if(direction.toStdString() == "Up")
    {
        dirItem = this->Up;
    }
    else if(direction.toStdString() == "Left")
    {
        dirItem = this->Left;
    }
    else if(direction.toStdString() == "Down")
    {
        dirItem = this->Down;
    }
    else if(direction.toStdString() == "Right")
    {
        dirItem = this->Right;
    }

    if(dirItem != nullptr)
    {
        QTreeWidgetItem* newItem = new QTreeWidgetItem(dirItem);
        newItem->setText(0, typeName);
        dirItem->addChild(newItem);
        return true;
    }
    return false;
}
void RequirementsTree::RemoveRequirement(QTreeWidgetItem* req)
{
    auto name = req->text(0);
    delete req;
    emit RemoveRequiremntPartner(name);
}

QTreeWidgetItem* RequirementsTree::isTypeAlreadyPresent(QString typeName)
{
    for(int j=0; j<this->topLevelItemCount(); j++)
    {
        for(int i=0; i< this->topLevelItem(j)->childCount(); i++)
        {
            if(this->topLevelItem(j)->child(i)->text(0) == typeName)
                return this->topLevelItem(j)->child(i);
        }
    }

    return nullptr;
}
