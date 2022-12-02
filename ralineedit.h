#ifndef RALINEEDIT_H
#define RALINEEDIT_H

#include "qlineedit.h"
#include "renderarea.h"

class RALineEdit : public QLineEdit
{
    Q_OBJECT

private:


public:
    explicit RALineEdit(RenderArea *parent);

protected:
    //bool eventFilter(QObject* obj, QEvent* event) override;

private:

public slots:
    //void onTextChange();

};

#endif // RALINEEDIT_H
