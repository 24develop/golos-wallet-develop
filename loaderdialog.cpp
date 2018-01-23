#include <QtGui/QMovie>

#include "loaderdialog.h"
#include "ui_loaderdialog.h"

LoaderDialog::LoaderDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::LoaderDialog) {
    ui->setupUi(this);

    auto *transferLoader = new QMovie(":/images/loader.gif");

    transferLoader->setScaledSize(QSize(50, 50));
    this->ui->loaderIconLabel->setMovie(transferLoader);

    transferLoader->start();
}

LoaderDialog::~LoaderDialog() {
    delete ui;
}

void LoaderDialog::setLoaderText(QString text) {
    this->ui->loaderTextLabel->setText(text);
}
