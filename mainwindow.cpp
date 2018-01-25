#include <QtGui/QMovie>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtCore/QThread>
#include "mainwindow.h"
#include "paymentdialog.h"

#include "ui_mainwindow.h"
#include "lib/Auth.h"
#include "transactionerrordialog.h"
#include "loaderdialog.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this->ui->loginBtn, SIGNAL(clicked(bool)), this, SLOT(login()));
    connect(this->ui->golosBalanceBtn, SIGNAL(clicked(bool)), this, SLOT(showGolosPaymentDialog()));
    connect(this->ui->gbgBalanceBtn, SIGNAL(clicked(bool)), this, SLOT(showGbgPaymentDialog()));
    connect(this->ui->logoutBtn, SIGNAL(clicked(bool)), this, SLOT(logout()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));

    this->ui->stackedWidget->setCurrentIndex(2);

    this->_ws = new SocketSender(QUrl("wss://ws.golos.io"));
    //this->_ws = new SocketSender(QUrl("wss://api.golos.cf"));
    //this->_ws = new SocketSender(QUrl("ws://127.0.0.1:8090"));

    connect(this->_ws, SIGNAL(sconnect()), this, SLOT(goToLoginScreen()));

    this->_caller = new ApiCaller(this->_ws);
    this->_api = new Api(this->_caller);

    QMovie *transferLoader = new QMovie(":/images/loader.gif");

    this->ui->movieLabel->setMovie(transferLoader);
    transferLoader->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::login() {
    const auto pixmap = QPixmap(":/images/user-icon.png");
    this->ui->userIconLabel->setPixmap(pixmap.scaled(QSize(50, 50), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    LoaderDialog loaderDialog(this);
    loaderDialog.setLoaderText("User data receiving...");
    loaderDialog.setAttribute(Qt::WA_DeleteOnClose);

    loaderDialog.show();

    this->refreshWalletData();

    loaderDialog.close();

    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showPaymentDialog(QString suffix) {
    PaymentDialog dialog(this);

    dialog.setAmountSuffix(suffix);

    connect(&dialog, SIGNAL(transfer(QString, QString, QString, QString)), this, SLOT(
            transfer(QString, QString, QString, QString)));

    dialog.exec();
}

void MainWindow::logout() {
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::exit() {
    this->close();
}

void MainWindow::transfer(QString to, QString amount, QString memo, QString password) {
    LoaderDialog loaderDialog(this);
    loaderDialog.setLoaderText("Transfer...");
    loaderDialog.setAttribute(Qt::WA_DeleteOnClose);

    loaderDialog.show();

    this->_api->init();

    this->_api->login("", "");

    auto wif = Auth::toWif(this->ui->nameLabel->text(), password, "active");


    const auto result = this->_api->transfer(wif, this->ui->nameLabel->text(), to, amount, memo);

    if (!result->getError().isUndefined() && !result->getError().isNull()) {
        qDebug() << "Error: " << result->getError().toObject()["message"].toString();

        TransactionErrorDialog errorDialog(this);

        errorDialog.setErrorMessage("Transaction error. Please try again");

        errorDialog.exec();
    } else {
        this->refreshWalletData();
    }

    loaderDialog.close();
}

void MainWindow::refreshWalletData() {
    auto account = this->_api->getAccount(this->ui->loginEdit->text());

    QString balance = account->getResult().toArray()[0].toObject()["balance"].toString();
    QString sbdBalance = account->getResult().toArray()[0].toObject()["sbd_balance"].toString();
    QString accountName = account->getResult().toArray()[0].toObject()["name"].toString();

    this->ui->golosBalanceBtn->setText(balance);
    this->ui->gbgBalanceBtn->setText(sbdBalance);

    this->ui->nameLabel->setText(accountName);
}

void MainWindow::goToLoginScreen() {
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showGolosPaymentDialog() {
    this->showPaymentDialog(" GOLOS");
}

void MainWindow::showGbgPaymentDialog() {
    this->showPaymentDialog(" GBG");
}
