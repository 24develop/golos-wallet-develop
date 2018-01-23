#ifndef LOADERDIALOG_H
#define LOADERDIALOG_H

#include <QDialog>

namespace Ui {
    class LoaderDialog;
}

class LoaderDialog : public QDialog {
Q_OBJECT

public:
    explicit LoaderDialog(QWidget *parent = 0);

    ~LoaderDialog();

    void setLoaderText(QString text);

private:
    Ui::LoaderDialog *ui;
};

#endif // LOADERDIALOG_H
