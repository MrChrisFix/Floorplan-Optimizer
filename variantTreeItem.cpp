#include "variantTreeItem.h"

variantTreeItem::variantTreeItem(QTreeWidgetItem *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings)
{

}

void variantTreeItem::setVariant(Variant* var)
{
    this->repVariant = var;
}

Variant* variantTreeItem::variant()
{
    return this->repVariant;
}
