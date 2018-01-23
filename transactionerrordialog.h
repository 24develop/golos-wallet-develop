#ifndef TRANSACTIONERRORDIALOG_H
#define TRANSACTIONERRORDIALOG_H

#include <QDialog>

namespace Ui {
    class TransactionErrorDialog;
}

class TransactionErrorDialog : public QDialog {
Q_OBJECT

public:
    explicit TransactionErrorDialog(QWidget *parent = 0);

    ~TransactionErrorDialog();

    void setErrorMessage(QString message);

private:
    Ui::TransactionErrorDialog *ui;
};

#endif // TRANSACTIONERRORDIALOG_H
