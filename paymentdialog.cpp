#include "paymentdialog.h"
#include "ui_paymentdialog.h"

PaymentDialog::PaymentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentDialog)
{
    ui->setupUi(this);
}

PaymentDialog::~PaymentDialog()
{
    delete ui;
}
