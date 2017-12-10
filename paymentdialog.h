#ifndef PAYMENTDIALOG_H
#define PAYMENTDIALOG_H

#include <QDialog>

namespace Ui {
class PaymentDialog;
}

class PaymentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentDialog(QWidget *parent = 0);
    ~PaymentDialog();

private:
    Ui::PaymentDialog *ui;

private slots:

    void emitTransfer();

signals:

    void transfer(QString to, QString amount, QString memo, QString password);
};

#endif // PAYMENTDIALOG_H
