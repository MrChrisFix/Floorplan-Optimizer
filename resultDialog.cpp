#include "resultDialog.h"
#include "Algorithm/Type.h"
#include "ui_resultDialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::setResults(unsigned width, unsigned height, std::vector<FPA::Variant*> combination)
{
    ui->height_info->setText(QString::number(height));
    ui->width_info->setText(QString::number(width));

    ui->typeTable->clearContents();
    ui->typeTable->setRowCount(0);
    int i=0;
    for(auto& var : combination)
    {
        QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(var->GetType()->GetName()));
        QTableWidgetItem* varWidth = new QTableWidgetItem(QString::number(var->GetWidth()));
        QTableWidgetItem* varHeight = new QTableWidgetItem(QString::number(var->GetHeight()));

        ui->typeTable->insertRow(i);
        ui->typeTable->setItem(i, 0, type);
        ui->typeTable->setItem(i, 1, varWidth);
        ui->typeTable->setItem(i, 2, varHeight);
    }
}

void ResultDialog::setResults(FPA::ResultStruct results)
{
    ui->height_info->setText(QString::number(results.bestHeight));
    ui->width_info->setText(QString::number(results.bestWidth));

    QString time;
    if(results.time_microsec > 1000000)
    {
        float num = results.time_microsec /1000000.0;
        time = QString::number(num) + "s";
    }
    else if(results.time_microsec > 1000)
    {
        float num = results.time_microsec /1000.0;
        time = QString::number(num) + "ms";
    }
    else
    {
        time = QString::number(results.time_microsec) + "µs";
    }


    ui->time_info->setText(time.toUtf8());

    ui->typeTable->clearContents();
    ui->typeTable->setRowCount(0);
    int i=0;
    for(auto& var : results.bestCombination)
    {
        QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(var->GetType()->GetName()));
        QTableWidgetItem* varWidth = new QTableWidgetItem(QString::number(var->GetWidth()));
        QTableWidgetItem* varHeight = new QTableWidgetItem(QString::number(var->GetHeight()));

        ui->typeTable->insertRow(i);
        ui->typeTable->setItem(i, 0, type);
        ui->typeTable->setItem(i, 1, varWidth);
        ui->typeTable->setItem(i, 2, varHeight);

        i++;
    }
}
