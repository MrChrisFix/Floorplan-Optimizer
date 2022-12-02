#ifndef RATEXTEDIT_H
#define RATEXTEDIT_H

#include "qtextedit.h"
#include "renderarea.h"

class RATextEdit : public QTextEdit
{
    Q_OBJECT

private:


public:
    explicit RATextEdit(RenderArea *parent);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:

public slots:
    void setValue();

};

#endif // RATEXTEDIT_H
