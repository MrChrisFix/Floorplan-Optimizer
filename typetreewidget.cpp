#include "typetreewidget.h"
#include "qmenu.h"

TypeTreeWidget::TypeTreeWidget(QWidget *parent) : QTreeWidget{parent}
{
    this->CreateContextMenus();

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenu(QPoint)));
}

TypeTreeWidget::~TypeTreeWidget()
{
    if(variantContextMenu != nullptr)
        delete variantContextMenu;
    if(typeContextMenu != nullptr)
        delete typeContextMenu;
}

void TypeTreeWidget::CreateContextMenus()
{
    //Types tree

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->typeContextMenu = new QMenu(this);
    this->variantContextMenu = new QMenu(this);

    QAction* renameAction = new QAction("Rename", this->typeContextMenu);
    this->typeContextMenu->addAction(renameAction);
    connect(renameAction, SIGNAL(triggered(bool)), this, SLOT(renameSlot()));

    QAction* deleteAction = new QAction("Delete", this);
    this->typeContextMenu->addAction(deleteAction);
    this->variantContextMenu->addAction(deleteAction);
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteSlot()));

    this->typeContextMenu->addSeparator();

    QAction* AddVariantAction = new QAction("Add new variant", this->typeContextMenu);
    this->typeContextMenu->addAction(AddVariantAction);
    connect(AddVariantAction, SIGNAL(triggered(bool)), this, SLOT(addVariantSlot()));
}

void TypeTreeWidget::renameSlot()
{

}
void TypeTreeWidget::deleteSlot()
{
    delete this->selectedItems()[0];
    this->typeContextMenu->hide();
}
void TypeTreeWidget::addVariantSlot()
{
    int number = this->selectedItems()[0]->childCount() + 1;
    QString name = QString("Variant ") + QString::number(number);
    bool originalName = true;
    do
    {
        originalName = true;
        for(int i =0; i< this->selectedItems()[0]->childCount(); i++)
        {
            if(this->selectedItems()[0]->child(i)->text(0) == name)
            {
                name = QString("Variant ") + QString::number(++number);
                originalName = false;
                break;
            }
        }
    }
    while(!originalName);
    QTreeWidgetItem* newVariant = new QTreeWidgetItem(this->selectedItems()[0], QStringList(name));
    this->selectedItems()[0]->addChild(newVariant);
}

void TypeTreeWidget::onContextMenu(const QPoint &point)
{
    auto item = this->itemAt(point);
    if(item == nullptr) return;
    if(item->parent() != nullptr) //Variant item
    {
        this->variantContextMenu->exec(this->viewport()->mapToGlobal(point));
    }
    else //Type item
    {
        this->typeContextMenu->exec(this->viewport()->mapToGlobal(point));
    }
}
