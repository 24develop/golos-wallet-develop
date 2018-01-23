#include "transactionerrordialog.h"
#include "ui_transactionerrordialog.h"

TransactionErrorDialog::TransactionErrorDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::TransactionErrorDialog) {
    ui->setupUi(this);
}

TransactionErrorDialog::~TransactionErrorDialog() {
    delete ui;
}

void TransactionErrorDialog::setErrorMessage(QString message) {
    this->ui->label->setText(message);
}
