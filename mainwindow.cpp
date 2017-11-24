#include "mainwindow.h"
#include "paymentdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(this->ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(sendCommand()));
    connect(this->ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(switchToMain()));
    connect(this->ui->commandLinkButton, SIGNAL(clicked(bool)), this, SLOT(showPaymentDialog()));
    connect(this->ui->commandLinkButton_2, SIGNAL(clicked(bool)), this, SLOT(showPaymentDialog()));
    connect(this->ui->commandLinkButton_3, SIGNAL(clicked(bool)), this, SLOT(showPaymentDialog()));

    this->_ws = new SocketSender(QUrl(QStringLiteral("wss://ws.golos.io")));
    this->_cmd = new CmdSender();
    this->_caller = new ApiCaller(this->_ws);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendCommand()
{
    Command* _command = new Command(40, "get_account_count", new QStringList());

    this->_caller->call(_command);
}

void MainWindow::switchToMain()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showPaymentDialog()
{
    PaymentDialog dialog(this);

    dialog.exec();
}
