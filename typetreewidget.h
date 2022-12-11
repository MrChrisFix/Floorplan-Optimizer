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

    std::vector<Alg::Type*> GetTypeVector();

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

    //void AddRequirement(char side, QString typeName);

public slots:
    void addNewType();
    void addNewType(QString name);

signals:
    void variantChanged(Alg::Variant*);

};

#endif // TYPETREEWIDGET_H
