#include "typeTreeItem.h"

TypeTreeItem::TypeTreeItem(QTreeWidget *treeview, const QStringList &strings) : QTreeWidgetItem(treeview, strings)
{
    this->repType = new FPA::Type(strings[0].toStdString());
}

TypeTreeItem::~TypeTreeItem()
{
    delete this->repType;
}

void TypeTreeItem::setType(FPA::Type* t)
{
    if(this->repType != nullptr)
        delete this->repType;
    this->repType = t;
}

FPA::Type* TypeTreeItem::getType()
{
    return this->repType;
}
