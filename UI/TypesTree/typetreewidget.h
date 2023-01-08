#ifndef TYPETREEWIDGET_H
#define TYPETREEWIDGET_H

#include "Algorithm/Variant.h"
#include "variantTreeItem.h"
#include <QTreeWidget>

class TypeTreeWidget : public QTreeWidget
{
    Q_OBJECT

private:
    QMenu* variantContextMenu;
    QMenu* typeContextMenu;

    QString oldTypeNameHolder;
    VariantTreeItem* lastSelected;

public:
    TypeTreeWidget(QWidget *parent);
    ~TypeTreeWidget();

    std::vector<FPA::Type*> GetTypeVector();
    void InsertTypeVector(std::vector<FPA::Type*> &types);

private:
    void CreateContextMenus();

private slots:
    void onContextMenu(const QPoint &point);

    void renameType();
    void checkNewName(QTreeWidgetItem* changedItem);
    void deleteTreeType();
    void deleteTreeVariant();
    void addNewVariant();

    void SelectionChange();

public slots:
    void addNewType();

signals:
    void variantChanged(FPA::Variant*);
    void TypeDeleted();
};

#endif // TYPETREEWIDGET_H
