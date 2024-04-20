#include<sstream>
#include<iostream>

#include"client.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::move;

Client::Client(){}

MessageHandler Client::init(const int argc, char* argv[]){

    if (argc != 3) {
        cerr << "Usage: client host-name port-number" << endl;
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

    MessageHandler mess(move(conn));
    return mess;
}

int Client::getPort(){return port;}

int Client::application(MessageHandler mess){
    int userInput = -1;
    bool InputCheck = true;

    while (InputCheck) {
        showOptions();

        //cin.ignore(100,'\n');
        cin >> userInput;
        cin.ignore(100,'\n');

        if(cin.fail()){
            error(1);
            cin.clear();
            cin.ignore(100,'\n');   // vet inte varför jag måste "cleara" den igen???
        }else{
            
            switch (userInput) 
            {
                case 1:
                    listNewsGroups(move(mess));
                    break;
                
                case 2:
                    createNewsGroups(move(mess));
                    break;
                
                case 3:
                    deleteNewsGroups(move(mess));
                    break;
                
                case 4:
                    listArticle(move(mess));
                    break;
                
                case 5:
                    cout << "hej5";
                    break;
                
                case 6:
                    cout << "hej6";
                    break;
                
                case 7:
                    cout << "hej7";
                    break;

                case 8:
                    cout << "Goodbye!" << endl;
                    InputCheck = false;
                    break;
                
                default:
                    error(1);
                    break;
            }
        }        
    }
    return 0;
}

void Client::showOptions(){
    cout << "\n";
    cout << "Choose an option:\n";
    cout << "(1) List NewsGroups\n";
    cout << "(2) Create a NewsGroup\n";
    cout << "(3) Delete a NewsGroup\n";
    cout << "(4) List Articles in a NewsGroups\n";
    cout << "(5) Create an Article\n";
    cout << "(6) Delete an Article\n";
    cout << "(7) Show an Article\n";
    cout << "(8) Terminat Client\n";
    cout << "Insert number: ";
}

void Client::error(int i){
    switch (i)
    {
    case -1:
        cerr << "Wrong answer from server! (should never be seen by user)" << endl;
        break;
    
    case 1:
        cerr << "Invalid Input. Input must contain a single number (1-8)" << endl;
        break;
    
    case 2:
        cerr << "Invalid Input. Input must consist of an Id (int)" << endl;
        break;

    default:
        break;
    }
}

void Client::listNewsGroups(MessageHandler mess){ //Done
    mess.sendCode(int(Protocol::COM_LIST_NG));
    mess.sendCode(int(Protocol::COM_END));

    if(mess.recvCode() == int(Protocol::ANS_LIST_NG)){
        int n = mess.recvInt();
        if(n != 0){
            cout << "Id : Name" << endl;
            for(int i = 0; i < n; i++){
                cout << mess.recvInt() << " : " << mess.recvStringParameter() << endl;
            }
        }else {
            cout << "No NewsGroups exists" << endl;
        }
        if(mess.recvCode() != int(Protocol::ANS_END)){
            error(-1);
        }
    }else{
        error(-1);
    }
    
}
void Client::createNewsGroups(MessageHandler mess){ //Done

    cout << "Enter name of new NewsGroup (Typ \"?c\" to cancel): ";
    string nameOfNewsGroup;
    std::getline(cin, nameOfNewsGroup);

    if(nameOfNewsGroup != "?c"){
        mess.sendCode(int(Protocol::COM_CREATE_NG));
        mess.sendStringParameter(nameOfNewsGroup);
        mess.sendCode(int(Protocol::COM_END));

        if(mess.recvCode() == int(Protocol::ANS_CREATE_NG)){
            int answerCode = mess.recvCode();
            if(answerCode == int(Protocol::ANS_ACK)){
                cout << "New NewsGroup created. Name: " << nameOfNewsGroup << endl;
            }else if(answerCode == int(Protocol::ANS_NAK)){
                if(mess.recvCode() == int(Protocol::ERR_NG_ALREADY_EXISTS)){
                    cout << "New NewsGroup not created. Reason: NewsGroup already exists." << endl;
                }else{
                    error(-1);
                }
            }else{
                error(-1);
            }
            if(mess.recvCode() != int(Protocol::ANS_END)){
                error(-1);
            }
        }else{
            error(-1);
        }
    }else{
        cout << "Command Canceled" << endl;
    }
    
}
void Client::deleteNewsGroups(MessageHandler mess){ //Done

    cout << "Enter Id of the NewsGroup you want to delete (Typ \"?c\" to cancel): ";
    int idOfNewsGroup;
    cin >> idOfNewsGroup;

    string temp;
    std::getline(cin, temp);

    if(!cin.fail()){
        if(temp == ""){
            mess.sendCode(int(Protocol::COM_DELETE_NG));
            mess.sendIntParameter(idOfNewsGroup);
            mess.sendCode(int(Protocol::COM_END));

            if(mess.recvCode() == int(Protocol::ANS_DELETE_NG)){
                int answerCode = mess.recvCode();
                if(answerCode == int(Protocol::ANS_ACK)){
                    cout << "NewsGroup (" << idOfNewsGroup << ") deleted." << endl;
                }else if(answerCode == int(Protocol::ANS_NAK)){
                    if(mess.recvCode() == int(Protocol::ERR_NG_DOES_NOT_EXIST)){
                        cout << "NewsGroup (" << idOfNewsGroup << ") not deleted. Reason: NewsGroup (" << idOfNewsGroup << ") does not exists." << endl;
                    }else{
                        error(-1);
                    }
                }else{
                    error(-1);
                }
                if(mess.recvCode() != int(Protocol::ANS_END)){
                    error(-1);
                }
            }else{
                error(-1);
            }
        }else{
            error(2);
        }
    }else{
        cin.clear();
        string userCommand;
        std::getline(cin, userCommand);
        if(userCommand != "?c"){
            error(2);
        }else{
            cout << "Command Canceled" << endl;
        }
    }
    
}
void Client::listArticle(MessageHandler mess){ //Done

    cout << "Enter Id of the NewsGroup to get the list of Articles (Typ \"?c\" to cancel): ";
    int idOfNewsGroupArticle;
    cin >> idOfNewsGroupArticle;

    string temp;
    std::getline(cin, temp);

    if(!cin.fail()){
        if(temp == ""){
            mess.sendCode(int(Protocol::COM_LIST_ART));
            mess.sendIntParameter(idOfNewsGroupArticle);
            mess.sendCode(int(Protocol::COM_END));

            if(mess.recvCode() == int(Protocol::ANS_LIST_ART)){
                int answerCode = mess.recvCode();
                if(answerCode == int(Protocol::ANS_ACK)){
                    int n = mess.recvInt();
                    if(n != 0){
                        cout << "Id : Name" << endl;
                        for(int i = 0; i < n; i++){
                            cout << mess.recvInt() << " : " << mess.recvStringParameter() << endl;
                        }
                    }else {
                        cout << "No Articles exists" << endl;
                    }
                }else if(answerCode == int(Protocol::ANS_NAK)){
                    if(mess.recvCode() == int(Protocol::ERR_NG_DOES_NOT_EXIST)){
                        cout << "Can not show list of Articles. Reason: NewsGroup (" << idOfNewsGroupArticle << ") does not exists." << endl;
                    }else{
                        error(-1);
                    }
                }else{
                    error(-1);
                }
                if(mess.recvCode() != int(Protocol::ANS_END)){
                    error(-1);
                }
            }else{
                error(-1);
            }
        }else{
            error(2);
        }
    }else{
        cin.clear();
        string userCommand;
        std::getline(cin, userCommand);
        if(userCommand != "?c"){
            error(2);
        }else{
            cout << "Command Canceled" << endl;
        }
    }
    
}
void Client::createArticle(MessageHandler mess){

}
void Client::deleteArticle(MessageHandler mess){

}
void Client::showArticle(MessageHandler mess){
    
}


int main(int argc, char* argv[]){
    // cout << "Choose a port for your Client: ";
    // int port;
    // cin >> port;
    Client userClient;
    MessageHandler mess = userClient.init(argc,argv);

    return userClient.application(move(mess));
}