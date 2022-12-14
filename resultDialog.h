#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include "Algorithm/resultStruct.h"
#include <QDialog>

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = nullptr);
    ~ResultDialog();

    void setResults(unsigned width, unsigned height, std::vector<FPA::Variant*> combination);
    void setResults(FPA::ResultStruct results);

private:
    Ui::ResultDialog *ui;
};

#endif // RESULTDIALOG_H
