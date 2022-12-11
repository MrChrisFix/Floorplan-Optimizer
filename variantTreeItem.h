#ifndef VARIANTTREEITEM_H
#define VARIANTTREEITEM_H

#include "Algorithm/Variant.h"
#include "typeTreeItem.h"
#include <QTreeWidgetItem>

class VariantTreeItem : public QTreeWidgetItem
{
private:
    Alg::Variant* repVariant;    ///Representing variant

public:
    VariantTreeItem(TypeTreeItem *parent, const QStringList &strings);
    ~VariantTreeItem();

    void setVariant(Alg::Variant* var);
    Alg::Variant* variant();
};

#endif // VARIANTTREEITEM_H
