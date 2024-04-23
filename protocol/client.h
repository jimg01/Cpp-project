#ifndef CLIENT_H
#define CLIENT_H

#include"messagehandler.h"
#include"connection.h"
#include"protocol.h"


class Client{
    public:
    Client();
    //~Client();
    MessageHandler init(const int, char*[]);
    int application(MessageHandler);
    int getPort();

    private:
    void showOptions();
    void error(const int);
    bool cancelCommand();
    void listNewsGroups(MessageHandler&);
    void createNewsGroups(MessageHandler&);
    void deleteNewsGroups(MessageHandler&);
    void listArticle(MessageHandler&);
    void createArticle(MessageHandler&);
    void deleteArticle(MessageHandler&);
    void showArticle(MessageHandler&);
    int port;


};

#endif