#include<iostream>

#include<cstdlib>
#include<filesystem>

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::move;
namespace fs = std::filesystem;

void showOptions(){
    cout << "0 Close" << endl;
    cout << "1 Make dir" << endl;
    cout << "2 show dir" << endl;
}

void optionOne(){
    cout << "Insert name of new dir: " << endl;
    string userInput;
    getline(cin, userInput);

    fs::path curPath = fs::current_path();
    string basePath = "/diskdatabase/test";
    fs::create_directory(string(curPath) + basePath + "/" + userInput);
}

int main(){
    bool whileCheck = true;
    while(whileCheck){

        showOptions();

        int userInput;
        cin >> userInput;

        switch(userInput)
        {
            case 0:
                whileCheck = false;
                break;

            case 1:
                optionOne();
                break;

            default:
                break;
        }

    }
}