#include <filesystem>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;

namespace fs = std::filesystem;

int main(){
	cout << "Name directory: " << endl;
	string dirName;
	cin >> dirName;
	cout << dirName << endl;
	cout << "this path " << fs::current_path() << endl;
	string path = fs::current_path();
	path.append("/");
	path.append(dirName);
	fs::create_directory(path);
	std::system("ls");

	int choice = -1;
	cout << "Removing  " << path << endl;
	cin >> choice;
	if(choice == 1){
		fs::remove(path);
	} else{
		cout << "Nothing was removed:" << endl;	
	}

	std::system("ls");
	
	
}
