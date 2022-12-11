#include "typeTreeItem.h"

TypeTreeItem::TypeTreeItem(QTreeWidget *treeview, const QStringList &strings) : QTreeWidgetItem(treeview, strings)
{
    this->repType = new Alg::Type(strings[0].toStdString());
}

TypeTreeItem::~TypeTreeItem()
{
    delete this->repType;
}

void TypeTreeItem::setType(Alg::Type* t)
{
    this->repType = t;
}
Alg::Type* TypeTreeItem::getType()
{
    return this->repType;
}
