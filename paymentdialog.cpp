#include "paymentdialog.h"
#include "ui_paymentdialog.h"

PaymentDialog::PaymentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(emitTransfer()));
}

PaymentDialog::~PaymentDialog()
{
    delete ui;
}

void PaymentDialog::emitTransfer() {
    this->transfer(this->ui->toEdit->text(), this->ui->amountSpinBox->text().replace(QLocale().decimalPoint(), "."),
                   this->ui->memoEdit->text(),
                   this->ui->passwordEdit->text());
}

void PaymentDialog::setAmountSuffix(QString suffix) {
    this->ui->amountSpinBox->setSuffix(suffix);
}
