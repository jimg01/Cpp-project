#include<sstream>
#include<iostream>

#include"client.h"
//#include"MH.h"

using std::string;
using std::cin;
using std::cout;

Client::Client(){}

bool Client::init(const int port){
    if(port == 1){
        Client::port = port;
        return true;
    }else{
        return false;
    }
}

int Client::getPort(){return port;}

int Client::application(){
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


int main(){
    cout << "Choose a port for your Client: ";
    int port;
    cin >> port;
    Client userClient;
    if(userClient.init(port)){
        cout << "Port exist, communication established!\n";
        return userClient.application();
    }else{
        cout << "Port failed, no communication\n";
        return 1;
    }
}