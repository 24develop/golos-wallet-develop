#include "apicaller.h"

ApiCaller::ApiCaller(WebSocketClient *sc, Cmd *cmd, QObject *parent):
    _socket(sc), _cmd(cmd)
{
}

void ApiCaller::call(Command *command)
{
    this->_socket->send(command->toJSON());
}

void ApiCaller::callCmd(Command *command)
{
    this->_cmd->send(command->toString());
}
