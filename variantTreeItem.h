#ifndef VARIANTTREEITEM_H
#define VARIANTTREEITEM_H

#include "Algorithm/Variant.h"
#include <QTreeWidgetItem>

class variantTreeItem : public QTreeWidgetItem
{
private:
    Variant* repVariant;    ///Representing variant

public:
    variantTreeItem(QTreeWidgetItem *parent, const QStringList &strings);

    void setVariant(Variant* var);
    Variant* variant();
};

#endif // VARIANTTREEITEM_H
