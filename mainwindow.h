#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "command.h"
#include "socketsender.h"
#include "apicaller.h"
#include "cmdsender.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SocketSender *_ws;
    ApiCaller *_caller;
    CmdSender *_cmd;

public slots:
    void sendCommand();
    void switchToMain();
    void showPaymentDialog();
};

#endif // MAINWINDOW_H
