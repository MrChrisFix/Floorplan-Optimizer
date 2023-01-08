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
    FPA::Type* currentType;

public:
    RequirementsTree(QWidget *parent);
    ~RequirementsTree();

private:
    QTreeWidgetItem* isTypeAlreadyPresent(QString typeName);
    void createBasicList();

public slots:
    void onChangedType(FPA::Variant* typeItem);
    bool addRequirement(QString direction, QString typeName);
    void RemoveRequirement(QTreeWidgetItem* req);
    void onDeleteAction();
    void onContextMenu(const QPoint &point);

signals:
    void RemoveRequiremntPartner(QString); //TypeName
};

#endif // REQUIREMENTSTREE_H
