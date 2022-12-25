#include "ralineedit.h"
#include <QKeyEvent>
#include <QIntValidator>

#include "renderarea.h"

RALineEdit::RALineEdit(RenderArea* parent)
{
    this->setParent(parent);

    this->setValidator( new QIntValidator(0, 1000, this));

    this->setText("1");
}
