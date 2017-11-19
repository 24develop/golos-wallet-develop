#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "command.h"
#include "websocketclient.h"
#include "apicaller.h"
#include "cmd.h"

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

    WebSocketClient *_ws;
    ApiCaller *_caller;
    Cmd *_cmd;

public slots:
    void sendCommand();
    void switchToMain();
    void showPaymentDialog();
};

#endif // MAINWINDOW_H
