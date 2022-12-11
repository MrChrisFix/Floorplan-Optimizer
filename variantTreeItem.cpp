#include "variantTreeItem.h"

VariantTreeItem::VariantTreeItem(TypeTreeItem *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings)
{
    Alg::Type* parentType = parent->getType();
    this->repVariant = new Alg::Variant(1,1, parentType);
}

void VariantTreeItem::setVariant(Alg::Variant* var)
{
    this->repVariant = var;
}

Alg::Variant* VariantTreeItem::variant()
{
    return this->repVariant;
}
