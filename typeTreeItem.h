#ifndef TYPETREEITEM_H
#define TYPETREEITEM_H

#include "Algorithm/Type.h"
#include <QTreeWidgetItem>

class TypeTreeItem : public QTreeWidgetItem
{
private:
    Alg::Type* repType; ///Representing Type object

public:
    TypeTreeItem(QTreeWidget *treeview, const QStringList &strings);

    void setType(Alg::Type* t);
    Alg::Type* getType();
};

#endif // TYPETREEITEM_H
