#include<sstream>
#include<iostream>
#include<algorithm>
#include<limits>
#include<vector>

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

    MessageHandler mess{};
    std::shared_ptr<Connection> connPtr = std::make_shared<Connection>(move(conn));
    mess.setConnection(connPtr);
    return mess;
}

int Client::getPort(){return port;}

int Client::application(MessageHandler& mess){

    int userInput = -1;
    bool InputCheck = true;

    while (InputCheck) {
        showOptions();

        if(cin >> userInput && cin.peek() == '\n'){
            cin.ignore();
            
            switch (userInput) 
            {
                case 1:
                    listNewsGroups(mess);
                    break;
                
                case 2:
                    createNewsGroups(mess);
                    break;
                
                case 3:
                    deleteNewsGroups(mess);
                    break;
                
                case 4:
                    listArticle(mess);
                    break;
                
                case 5:
                    createArticle(mess);
                    break;
                
                case 6:
                    deleteArticle(mess);
                    break;
                
                case 7:
                    showArticle(mess);
                    break;

                case 8:
                    cout << "Goodbye!" << endl;
                    InputCheck = false;
                    break;
                
                default:
                    error(1);
                    break;
            }
//            cout << "In connected? " << mess.isConnected();
        }else {
            error(1);
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if(cin.eof()){
            break;
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

    case 3:
        cerr << "Invalid Input. Input must consist of a char (y/n)" << endl;
        break;

    case 4:
        cerr << "Invalid Input. NewsGroup name can not be empty" << endl;
        break;

    case 5:
        cerr << "Invalid Input. Article name can not be empty" << endl;
        break;

    case 6:
        cerr << "Invalid Input. Article author can not be empty" << endl;
        break;

    case 7:
        cerr << "Invalid Input. Article text can not be empty" << endl;
        break;

    default:
        break;
    }
}

bool Client::cancelCommand(){
    cout << "Ready to continue (y/n)?: ";
    string userInput;
    getline(cin, userInput);
    std::transform(userInput.begin(), userInput.end(),userInput.begin(),[](unsigned char c) {return std::tolower(c);});
    if(userInput == "y"){
        //return true;
        return false;
    }else if(userInput == "n"){
        cout << "Command Canceled" << endl;
        //return false;
        return true;
    }else {
        error(3);
        return cancelCommand();
    }
}

void Client::listNewsGroups(MessageHandler& mess){ 
    mess.sendCode(char(Protocol::COM_LIST_NG));
    mess.sendCode(char(Protocol::COM_END));

    if(mess.recvCode() == char(Protocol::ANS_LIST_NG)){
        int n = mess.recvIntParameter();
        if(n != 0){
            cout << "NewsGroups:" << endl;
            cout << "Id : Name" << endl;
            for(int i = 0; i < n; i++){
                cout << mess.recvIntParameter() << " : " << mess.recvStringParameter() << endl;
            }
        }else {
            cout << "No NewsGroups exists" << endl;
        }
        if(mess.recvCode() != char(Protocol::ANS_END)){
            error(-1);
        }
    }else{
        error(-1);
    }
    
}

void Client::createNewsGroups(MessageHandler& mess){ 
    bool inputCheck = true;
    string nameOfNewsGroup;

    while(inputCheck){
        cout << "Enter name of new NewsGroup: ";
        std::getline(cin, nameOfNewsGroup);
        if(nameOfNewsGroup == ""){
            error(4);
        }else{
            inputCheck = false;
        }
    }

    if(!cancelCommand()){	// added "!" for the naming and output to make more sense
		
        mess.sendCode(char(Protocol::COM_CREATE_NG));
        mess.sendStringParameter(nameOfNewsGroup);
        mess.sendCode(char(Protocol::COM_END));

		//can throw ClosedConnectionException!
        if(mess.recvCode() == char(Protocol::ANS_CREATE_NG)){	
        	//cout << "server created nresgrupp" << endl;
            int answerCode = mess.recvCode();
            if(answerCode == char(Protocol::ANS_ACK)){
                cout << "New NewsGroup created. Name: " << nameOfNewsGroup << endl;
            }else if(answerCode == char(Protocol::ANS_NAK)){
                if(mess.recvCode() == char(Protocol::ERR_NG_ALREADY_EXISTS)){
                    cout << "Invalid Input." << endl;
                    cout << "Reason: NewsGroup already exists." << endl;
                }else{
                    error(-1);
                }
            }else{
                error(-1);
            }
            if(mess.recvCode() != char(Protocol::ANS_END)){
                error(-1);
            }
        }else{
            error(-1);
        }
    }
    
}

void Client::deleteNewsGroups(MessageHandler& mess){ 

    cout << "Enter Id of the NewsGroup to delete: ";
    int idOfNewsGroup;
    if(cin >> idOfNewsGroup && cin.peek() == '\n'){
        cin.ignore();

        if(!cancelCommand()){
            mess.sendCode(char(Protocol::COM_DELETE_NG));
            mess.sendIntParameter(idOfNewsGroup);
            mess.sendCode(char(Protocol::COM_END));

            if(mess.recvCode() == char(Protocol::ANS_DELETE_NG)){
                int answerCode = mess.recvCode();
                if(answerCode == char(Protocol::ANS_ACK)){
                    cout << "NewsGroup (" << idOfNewsGroup << ") was deleted." << endl;
                }else if(answerCode == char(Protocol::ANS_NAK)){
                    if(mess.recvCode() == char(Protocol::ERR_NG_DOES_NOT_EXIST)){
                        cout << "Invalid Input." << endl;
                        cout << "Reason: NewsGroup (" << idOfNewsGroup << ") does not exists." << endl;
                    }else{
                        error(-1);
                    }
                }else{
                    error(-1);
                }
                if(mess.recvCode() != char(Protocol::ANS_END)){
                    error(-1);
                }
            }else{
                error(-1);
            }
        }
    }else{
        error(2);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
}

void Client::listArticle(MessageHandler& mess){ 

    cout << "Enter Id of the NewsGroup to get the list of Articles: ";
    int idOfNewsGroupArticle;
    if(cin >> idOfNewsGroupArticle && cin.peek() == '\n'){
        cin.ignore();

        if(true){
            mess.sendCode(char(Protocol::COM_LIST_ART));
            mess.sendIntParameter(idOfNewsGroupArticle);
            mess.sendCode(char(Protocol::COM_END));

            if(mess.recvCode() == char(Protocol::ANS_LIST_ART)){
                int answerCode = mess.recvCode();
                if(answerCode == char(Protocol::ANS_ACK)){
                    int n = mess.recvIntParameter();
                    if(n != 0){
                        cout << "Articles:" << endl;
                        cout << "Id : Name" << endl;
                        for(int i = 0; i < n; i++){
                            cout << mess.recvIntParameter() << " : " << mess.recvStringParameter() << endl;
                        }
                    }else {
                        cout << "No Articles exists in Newsgroup (" << idOfNewsGroupArticle << ")" << endl;
                    }
                }else if(answerCode == char(Protocol::ANS_NAK)){
                    if(mess.recvCode() == char(Protocol::ERR_NG_DOES_NOT_EXIST)){
                        cout << "Invalid Input." << endl;
                        cout << "Reason: NewsGroup (" << idOfNewsGroupArticle << ") does not exists." << endl;
                    }else{
                        error(-1);
                    }
                }else{
                    error(-1);
                }
                if(mess.recvCode() != char(Protocol::ANS_END)){
                    error(-1);
                }
            }else{
                error(-1);
            }
        }
    }else{
        error(2);
        cin.clear();        
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
}

void Client::createArticle(MessageHandler& mess){

    cout << "Enter Id of NewsGroup where Article should be created: ";
    int idOfNewsGroup;

    if(cin >> idOfNewsGroup && cin.peek() == '\n'){
        cin.ignore();

        bool inputCheck = true;
        string articleName, articleAuthor, articleText;

        while(inputCheck){
            cout << "Enter Article name: ";
            getline(cin, articleName);
            if(articleName == ""){
                error(5);
            }else{
                inputCheck = false;
            }
        }
        inputCheck = true;

        while(inputCheck){
            cout << "Enter Article author: ";
            getline(cin, articleAuthor);
            if(articleAuthor == ""){
                error(6);
            }else{
                inputCheck = false;
            }
        }
        inputCheck = true;

        while(inputCheck){
            cout << "Enter Article text (multiple lines)(end of Article write \"end\" on last line): " << endl;
            string articleLine;
            getline(cin, articleLine);
            while(articleLine.compare("end") != 0){
                articleText.append(articleLine + "\n");
                getline(cin, articleLine);
            }
            inputCheck = false;
        }                  

        if(!cancelCommand()){

            mess.sendCode(char(Protocol::COM_CREATE_ART));
            mess.sendIntParameter(idOfNewsGroup);
            mess.sendStringParameter(articleName);
            mess.sendStringParameter(articleAuthor);
            mess.sendStringParameter(articleText);
            mess.sendCode(char(Protocol::COM_END));

            if(mess.recvCode() == char(Protocol::ANS_CREATE_ART)){
                int answerCode = mess.recvCode();
                if(answerCode == char(Protocol::ANS_ACK)){
                    cout << "New Article created." << endl;
                    cout << "Name: " << articleName << endl;
                    cout << "Author: " << articleAuthor << endl;
                    cout << "Text: " << endl;
                    cout << articleText << endl;
                }else if(answerCode == char(Protocol::ANS_NAK)){
                    if(mess.recvCode() == char(Protocol::ERR_NG_DOES_NOT_EXIST)){
                        cout << "Invalid Input." << endl;
                        cout << "Reason: NewsGroup (" << idOfNewsGroup << ") does not exists." << endl;
                    }else{
                        error(-1);
                    }
                }else{
                    error(-1);
                }
                if(mess.recvCode() != char(Protocol::ANS_END)){
                    error(-1);
                }
            }else{
                error(-1);
            }
        }
    }else{
        error(2);
        cin.clear();        
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

}

void Client::deleteArticle(MessageHandler& mess){ 

    cout << "Enter Id of NewsGroup where Article should be deleted: ";
    int idOfNewsGroup, idOfArticle;

    if(cin >> idOfNewsGroup && cin.peek() == '\n'){
        cin.ignore();

        cout << "Enter Id of Article that should be deleted: ";

        if(cin >> idOfArticle && cin.peek() == '\n'){
            cin.ignore();

            if(!cancelCommand()){
                mess.sendCode(char(Protocol::COM_DELETE_ART));
                mess.sendIntParameter(idOfNewsGroup);
                mess.sendIntParameter(idOfArticle);
                mess.sendCode(char(Protocol::COM_END));

                if(mess.recvCode() == char(Protocol::ANS_DELETE_ART)){
                    int answerCode = mess.recvCode();
                    if(answerCode == char(Protocol::ANS_ACK)){
                        cout << "Article (" << idOfArticle << ") was deleted." << endl;
                    }else if(answerCode == char(Protocol::ANS_NAK)){
                        int answerErrorCode = mess.recvCode();
                        cout << "Invalid Input." << endl;
                        if(answerErrorCode == char(Protocol::ERR_NG_DOES_NOT_EXIST)){
                            cout << "Reason: NewsGroup (" << idOfNewsGroup << ") does not exists." << endl;
                        }else if(answerErrorCode == char(Protocol::ERR_ART_DOES_NOT_EXIST)){
                            cout << "Reason: Article (" << idOfArticle << ") does not exists." << endl;
                        }else{
                            error(-1);
                        }
                    }else{
                        error(-1);
                    }
                    if(mess.recvCode() != char(Protocol::ANS_END)){
                        error(-1);
                    }
                }else{
                    error(-1);
                }
            }
        }else{
            error(2);
            cin.clear();        
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }else{
        error(2);
        cin.clear();        
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Client::showArticle(MessageHandler& mess){

    cout << "Enter Id of NewsGroup where Article is: ";
    int idOfNewsGroup, idOfArticle;

    if(cin >> idOfNewsGroup && cin.peek() == '\n'){
        cin.ignore();

        cout << "Enter Id of Article to shown: ";

        if(cin >> idOfArticle && cin.peek() == '\n'){
            cin.ignore();

            if(true){
                mess.sendCode(char(Protocol::COM_GET_ART));
                mess.sendIntParameter(idOfNewsGroup);
                mess.sendIntParameter(idOfArticle);
                mess.sendCode(char(Protocol::COM_END));

                if(mess.recvCode() == char(Protocol::ANS_GET_ART)){
                    int answerCode = mess.recvCode();
                    if(answerCode == char(Protocol::ANS_ACK)){
                        
                        string articleName, articleAuthor, articleText;

                        articleName = mess.recvStringParameter();
                        articleAuthor = mess.recvStringParameter();
                        articleText = mess.recvStringParameter();

                        cout << "Article (" << idOfArticle << "):" << endl;
                        cout << "Name: " << articleName << endl;
                        cout << "Author: " << articleAuthor << endl;
                        cout << "Text: " << endl << articleText << endl;

                    }else if(answerCode == char(Protocol::ANS_NAK)){
                        int answerErrorCode = mess.recvCode();
                        cout << "Invalid Input." << endl;
                        if(answerErrorCode == char(Protocol::ERR_NG_DOES_NOT_EXIST)){
                            cout << "Reason: NewsGroup (" << idOfNewsGroup << ") does not exists." << endl;
                        }else if(answerErrorCode == char(Protocol::ERR_ART_DOES_NOT_EXIST)){
                            cout << "Reason: Article (" << idOfArticle << ") does not exists." << endl;
                        }else{
                            error(-1);
                        }
                    }else{
                        error(-1);
                    }
                    if(mess.recvCode() != char(Protocol::ANS_END)){
                        error(-1);
                    }
                }else{
                    error(-1);
                }
            }
        }else{
            error(2);
            cin.clear();        
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }else{
        error(2);
        cin.clear();        
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


int main(int argc, char* argv[]){
    
    Client userClient;
    MessageHandler mess = userClient.init(argc,argv);

    return userClient.application(mess);
}
