#include<sstream>
#include<iostream>

#include"client.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

Client::Client(){}

MessageHandler Client::init(const int argc, char* argv[]){

    if (argc != 3) {
                cerr << "Usage: myclient host-name port-number" << endl;
                exit(1);
        }

        int port = -1;
        try {
                port = std::stoi(argv[2]);
        } catch (std::exception& e) {
                cerr << "Wrong port number. " << e.what() << endl;
                exit(2);
        }

        Connection conn(argv[1], port);
        if (!conn.isConnected()) {
                cerr << "Connection attempt failed" << endl;
                exit(3);
        }

        MessageHandler mess(std::move(conn));
        return mess;
}

int Client::getPort(){return port;}

int Client::application(MessageHandler mess){
    int num = showOptions();
    cout << num << "\n";

    return 0;
}

int Client::showOptions(){
    cout << "\n";
    cout << "Choose an option:\n";
    cout << "(1) List NewsGroups\n";
    cout << "(2) Create a NewsGroup\n";
    cout << "(3) Delete a NewsGroup\n";
    cout << "(4) List Articles in a NewsGroups\n";
    cout << "(5) Create an Article\n";
    cout << "(6) Delete an Article\n";
    cout << "(7) Show an Article\n";
    cout << "Insert number: ";
    int num;
    cin >> num;
    return num;
}


int main(int argc, char* argv[]){
    // cout << "Choose a port for your Client: ";
    // int port;
    // cin >> port;
    Client userClient;
    MessageHandler mess = userClient.init(argc,argv);

    return userClient.application(std::move(mess));
}