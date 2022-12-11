#include "typeTreeItem.h"

TypeTreeItem::TypeTreeItem(QTreeWidgetItem *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings)
{

}

void TypeTreeItem::setType(Alg::Type* t)
{
    this->repType = t;
}
Alg::Type* TypeTreeItem::type()
{
    return this->repType;
}
