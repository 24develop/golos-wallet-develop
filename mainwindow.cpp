#include "mainwindow.h"
#include "paymentdialog.h"

#include "cmake-build-debug/hackaton_wallet_autogen/include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this->ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(login()));
    connect(this->ui->golosBalanceBtn, SIGNAL(clicked(bool)), this, SLOT(showPaymentDialog()));
    connect(this->ui->gbgBalanceBtn, SIGNAL(clicked(bool)), this, SLOT(showPaymentDialog()));
    connect(this->ui->actionLogout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));

    this->_ws = new SocketSender(QUrl(QStringLiteral("wss://ws.golos.io")));
    this->_caller = new ApiCaller(this->_ws);
    this->_api = new Api(this->_caller);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::login() {
    auto account = this->_api->getAccount(this->ui->loginEdit->text());

    QString balance = account->getResult()[0].toObject()["balance"].toString();
    QString sbdBalance = account->getResult()[0].toObject()["sbd_balance"].toString();
    QString accountName = account->getResult()[0].toObject()["name"].toString();

    this->ui->golosBalanceBtn->setText(balance);
    this->ui->gbgBalanceBtn->setText(sbdBalance);

    this->ui->nameLabel->setText(accountName);

    this->ui->stackedWidget->setCurrentIndex(1);
    this->ui->actionLogout->setEnabled(true);
}

void MainWindow::showPaymentDialog() {
    PaymentDialog dialog(this);

    dialog.exec();
}

void MainWindow::logout() {
    this->ui->actionLogout->setEnabled(false);

    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::exit() {
    this->close();
}
