#ifndef TYPETREEITEM_H
#define TYPETREEITEM_H

#include "Algorithm/Type.h"
#include <QTreeWidgetItem>

class TypeTreeItem : public QTreeWidgetItem
{
private:
    FPA::Type* repType; ///Representing Type object

public:
    TypeTreeItem(QTreeWidget *treeview, const QStringList &strings);
    ~TypeTreeItem();

    void setType(FPA::Type* t);
    FPA::Type* getType();
};

#endif // TYPETREEITEM_H
