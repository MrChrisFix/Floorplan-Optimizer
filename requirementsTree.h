#ifndef REQUIREMENTSTREE_H
#define REQUIREMENTSTREE_H

#include "Algorithm/Variant.h"
#include <QTreeWidget>

class RequirementsTree : public QTreeWidget
{
    Q_OBJECT

private:
    QTreeWidgetItem *Up, *Left, *Down, *Right;
    QMenu* contextMenu;
    Alg::Type* currentType;

public:
    RequirementsTree(QWidget *parent);

public slots:
    void onChangedType(Alg::Variant* typeItem);
    void addRequirement(QString direction, QString typeName);
    void RemoveRequirement(QTreeWidgetItem* req);
};

#endif // REQUIREMENTSTREE_H
