#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include "Algorithm/ResultStruct.h"
#include <QDialog>

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT
private:
    FPA::ResultStruct* _results;

public:
    explicit ResultDialog(QWidget *parent = nullptr);
    ~ResultDialog();

    void setResults(FPA::ResultStruct* results);

private:
    Ui::ResultDialog *ui;
};

#endif // RESULTDIALOG_H
