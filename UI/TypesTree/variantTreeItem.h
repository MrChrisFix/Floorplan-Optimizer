#ifndef VARIANTTREEITEM_H
#define VARIANTTREEITEM_H

#include "Algorithm/Variant.h"
#include "typeTreeItem.h"
#include <QTreeWidgetItem>

class VariantTreeItem : public QTreeWidgetItem
{
private:
    FPA::Variant* repVariant;    ///Representing variant

public:
    VariantTreeItem(TypeTreeItem *parent, const QStringList &strings);
    ~VariantTreeItem();

    void setVariant(FPA::Variant* var);
    FPA::Variant* variant();
};

#endif // VARIANTTREEITEM_H
