#include "requirementsTree.h"

RequirementsTree::RequirementsTree(QWidget *parent) : QTreeWidget(parent)
{
    this->Up = new QTreeWidgetItem(this, QStringList("Up"));
    this->Left = new QTreeWidgetItem(this, QStringList("Left"));
    this->Down = new QTreeWidgetItem(this, QStringList("Down"));
    this->Right = new QTreeWidgetItem(this, QStringList("Right"));
    QList<QTreeWidgetItem*> list;
    list.append(Up);
    list.append(Left);
    list.append(Down);
    list.append(Right);
    this->addTopLevelItems(list);
}
