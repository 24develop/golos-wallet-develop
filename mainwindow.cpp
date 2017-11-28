#include "mainwindow.h"
#include "paymentdialog.h"

#include "cmake-build-debug/hackaton_wallet_autogen/include/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this->ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(sendCommand()));
    //connect(this->ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(switchToMain()));
    connect(this->ui->golosBalanceBtn, SIGNAL(clicked(bool)), this, SLOT(showPaymentDialog()));
    connect(this->ui->gbgBalanceBtn, SIGNAL(clicked(bool)), this, SLOT(showPaymentDialog()));
    connect(this->ui->actionLogout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));

    this->_ws = new SocketSender(QUrl(QStringLiteral("wss://ws.golos.io")));
    this->_cmd = new CmdSender();
    this->_caller = new ApiCaller(this->_ws);
    this->_api = new Api(this->_caller);

    connect(this->_ws, SIGNAL(respond(Response * )), this->_api, SLOT(listener(Response * )));
    connect(this->_api, SIGNAL(getAccountRespond(Response * )), this, SLOT(receivedResponse(Response * )));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::sendCommand() {
    this->_api->getAccount(this->ui->lineEdit->text());
}

void MainWindow::switchToMain() {
    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showPaymentDialog() {
    PaymentDialog dialog(this);

    dialog.exec();
}

void MainWindow::receivedResponse(Response *response) {
    qDebug() << "Response ID: " << response->getId();

    QString balance = response->getResult()[0].toObject()["balance"].toString();
    QString sbdBalance = response->getResult()[0].toObject()["sbd_balance"].toString();
    QString accountName = response->getResult()[0].toObject()["name"].toString();

    this->ui->golosBalanceBtn->setText(balance);
    this->ui->gbgBalanceBtn->setText(sbdBalance);

    this->ui->label_2->setText(accountName);

    this->ui->stackedWidget->setCurrentIndex(1);
    this->ui->actionLogout->setEnabled(true);
}

void MainWindow::logout() {
    this->ui->actionLogout->setEnabled(false);

    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::exit() {
    this->close();
}
