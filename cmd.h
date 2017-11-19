#ifndef CMD_H
#define CMD_H

#include <QObject>
#include <QProcess>

class Cmd : public QObject
{
    Q_OBJECT
public:
    explicit Cmd(QObject *parent = nullptr);

private:
    QProcess *_current;

signals:

public slots:
    void send(QString data);
    void on_response();
};

#endif // CMD_H
