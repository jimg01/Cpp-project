#ifndef CLIENT_H
#define CLIENT_H

#include"messagehandler.h"
#include"connection.h"


class Client{
    public:
    Client();
    //~Client();
    MessageHandler init(const int, char*[]);
    int application(MessageHandler mess);
    int getPort();

    private:
    int showOptions();
    int port;


};

#endif