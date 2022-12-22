#include "variantTreeItem.h"
#include <algorithm>

VariantTreeItem::VariantTreeItem(TypeTreeItem *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings)
{
    Alg::Type* parentType = parent->getType();
    this->repVariant = new Alg::Variant(1,1, parentType);
}

VariantTreeItem::~VariantTreeItem()
{
    if(this->parent() != nullptr)
    {
        ((TypeTreeItem*)this->parent())->getType()->RemoveVariant(this->repVariant);
        delete this->repVariant;
    }

    // else
    // this->repVariant has been deleted by Type destructor, which has been invoked by TypeTreeItem destructor
}

void VariantTreeItem::setVariant(Alg::Variant* var)
{
    if(this->repVariant != nullptr)
        delete this->repVariant;
    this->repVariant = var;
}

Alg::Variant* VariantTreeItem::variant()
{
    return this->repVariant;
}
