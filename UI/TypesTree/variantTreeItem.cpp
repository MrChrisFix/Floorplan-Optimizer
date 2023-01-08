#include "variantTreeItem.h"
#include <algorithm>

VariantTreeItem::VariantTreeItem(TypeTreeItem *parent, const QStringList &strings) : QTreeWidgetItem(parent, strings)
{
    FPA::Type* parentType = parent->getType();
    this->repVariant = new FPA::Variant(1,1, parentType);
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

void VariantTreeItem::setVariant(FPA::Variant* var)
{
    if(this->repVariant != nullptr)
        delete this->repVariant;
    this->repVariant = var;
}

FPA::Variant* VariantTreeItem::variant()
{
    return this->repVariant;
}
