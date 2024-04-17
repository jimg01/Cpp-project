#ifndef CLIENT_H
#define CLIENT_H

class Client{
    public:
    Client();
    //~Client();
    bool init(const int);
    int application();
    int getPort();

    private:
    int showOptions();
    int port;


};

#endif