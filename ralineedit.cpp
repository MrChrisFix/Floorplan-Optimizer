#include "ralineedit.h"
#include "qcoreevent.h"
#include <QKeyEvent>

#include "renderarea.h"

RALineEdit::RALineEdit(RenderArea* parent)
{
    this->setParent(parent);
}

/*bool RATextEdit::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress) //NIE DZIA?A!!!!!!!!!!!! >:-(
    {
        QKeyEvent* key = (QKeyEvent*)event;
        if(key->key() == Qt::Key_NumberSign)
        {
            int num = key->key();
            this->setText(std::to_string(num).c_str());
        }
        else
        {
            return QTextEdit::eventFilter(obj, event);
        }
        return true;
    }

    return QTextEdit::eventFilter(obj, event);
}*/

void RALineEdit::setValue()
{
}
