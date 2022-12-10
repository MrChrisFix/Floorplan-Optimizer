#ifndef TYPETREEWIDGET_H
#define TYPETREEWIDGET_H

#include <QTreeWidget>

class TypeTreeWidget : public QTreeWidget
{
    Q_OBJECT

private:
    QMenu* variantContextMenu;
    QMenu* typeContextMenu;

public:
    TypeTreeWidget(QWidget *parent);
    ~TypeTreeWidget();

    void GetTypeVector(); //TODO: return will be vector<Type*>

private:
    void CreateContextMenus();

private slots:
    void onContextMenu(const QPoint &point);

    void renameType();
    void checkNewName(QTreeWidgetItem* changedItem);
    void deleteTreeItem();
    void addNewVariant();

public slots:
    void addNewType();
    void addNewType(QString name);

};

#endif // TYPETREEWIDGET_H
