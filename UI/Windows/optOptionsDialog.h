#ifndef OPTOPTIONSDIALOG_H
#define OPTOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptOptionsDialog;
}

class OptOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptOptionsDialog(QWidget *parent = nullptr);
    ~OptOptionsDialog();

    bool useMultithread();
    unsigned int getThreadNum();

private:
    Ui::OptOptionsDialog *ui;

private slots:
    void changeThreadLabel(int newVal);
    void disableThreadSlider();
};

#endif // OPTOPTIONSDIALOG_H
