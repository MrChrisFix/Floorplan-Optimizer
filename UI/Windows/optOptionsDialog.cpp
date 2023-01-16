#include "optOptionsDialog.h"
#include "ui_optOptionsDialog.h"

OptOptionsDialog::OptOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptOptionsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Options");

    this->ui->radioButtonNo->setChecked(true);
    this->ui->threadAmountSlider->setDisabled(true);
    this->ui->ThreadNumLabel->setText(QString::number(this->ui->threadAmountSlider->value()) + " threads");

    connect(ui->threadAmountSlider, SIGNAL(valueChanged(int)), this, SLOT(changeThreadLabel(int)));
    connect(ui->radioButtonNo, SIGNAL(toggled(bool)), this, SLOT(disableThreadSlider()));
}

OptOptionsDialog::~OptOptionsDialog()
{
    delete ui;
}

bool OptOptionsDialog::useMultithread()
{
    return this->ui->radioButtonYes->isChecked();
}
unsigned int OptOptionsDialog::getThreadNum()
{
    if(!this->useMultithread()) return 0;

    return this->ui->threadAmountSlider->value();
}

void OptOptionsDialog::changeThreadLabel(int newVal)
{
    this->ui->ThreadNumLabel->setText(QString::number(newVal) + " threads");
}

void OptOptionsDialog::disableThreadSlider()
{
    this->ui->threadAmountSlider->setEnabled(this->useMultithread());
}
