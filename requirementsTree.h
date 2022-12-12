#ifndef REQUIREMENTSTREE_H
#define REQUIREMENTSTREE_H

#include <QTreeWidget>

class RequirementsTree : public QTreeWidget
{
    Q_OBJECT

private:
    QTreeWidgetItem *Up, *Left, *Down, *Right;

public:
    RequirementsTree(QWidget *parent);
};

#endif // REQUIREMENTSTREE_H
