#ifndef TYPETREEITEM_H
#define TYPETREEITEM_H

#include "Algorithm/Type.h"
#include <QTreeWidgetItem>

class TypeTreeItem : public QTreeWidgetItem
{
private:
    Alg::Type* repType; ///Represemnting Type object

public:
    TypeTreeItem(QTreeWidgetItem *parent, const QStringList &strings);

    void setType(Alg::Type* t);
    Alg::Type* type();
};

#endif // TYPETREEITEM_H
