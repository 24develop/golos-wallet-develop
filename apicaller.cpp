#include "apicaller.h"

ApiCaller::ApiCaller(CommandSender *sender, QObject *parent):
    _sender(sender)
{
}

void ApiCaller::call(Command *command)
{
    this->_sender->send(command);
}
