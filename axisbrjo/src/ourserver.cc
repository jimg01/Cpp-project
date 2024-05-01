#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"
#include "database_interface.h"
#include "inmemorydatabase.h"
#include "diskdatabase.h"
#include "protocol.h"
#include "protocolviolationexception.h"
#include "messagehandler.h"

#include <iostream>
#include <memory>
#include <stdexcept>

using std::string;
using std::cout;
using std::cerr;
using std::endl;


Server init(int argc, char* argv[], std::shared_ptr<Database_interface>& dataPtr)
{
        if (argc != 3) {
                cerr << "Usage: ourserver port-number database-number(1=inmemory,2=disk)" << endl;
                exit(1);
        }

        int port = -1;
        try {
                port = std::stoi(argv[1]);
        } catch (std::exception& e) {
                cerr << "Wrong format for port number. " << e.what() << endl;
                exit(2);
        }

        Server server(port);
        if (!server.isReady()) {
                cerr << "Server initialization error." << endl;
                exit(3);
        }

        int databasetype;
        try
        {
            databasetype = std::stoi(argv[2]);
        }
        catch(const std::exception& e)
        {
            cerr << "Wrong format for database number. " << e.what() << endl;
            exit(4);
        }

        if(databasetype == 1){
    	    dataPtr = std::make_unique<InMemoryDatabase>();
        }else if(databasetype == 2){
            dataPtr = std::make_unique<DiskDatabase>();
        }else{
            cerr << "Database number must be 1 or 2." << endl;
            exit(5);
        }

        return server;
}

void listNewsGroups(MessageHandler& mess, Database_interface& database){

    /*
	COM_LIST_NG COM_END
	ANS_LIST_NG num_p [num_p string_p]* ANS_END
	*/
	
	if (mess.recvCode() == char(Protocol::COM_END)){
		auto list_of_newsgroups = database.list_NG();
		mess.sendCode(char(Protocol::ANS_LIST_NG));
		mess.sendIntParameter(list_of_newsgroups.size());
		for(auto it = list_of_newsgroups.begin(); it != list_of_newsgroups.end(); ++it){
			mess.sendIntParameter((*it).first);
			mess.sendStringParameter((*it).second);
		}
		mess.sendCode(char(Protocol::ANS_END));
	} else{
		//throw some error
		std::cerr << "Protocol violation in list NGs" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
	}

}

void createNewsGroups(MessageHandler& mess, Database_interface& database){

    /*
	COM_CREATE_NG string_p COM_END
	ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
	*/
	bool success = database.create_NG(mess.recvStringParameter());
	if (mess.recvCode() != int(char(Protocol::COM_END))){
		//Throw error;
		std::cerr << "Protocol violation in create NG" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
	}
	mess.sendCode(char(Protocol::ANS_CREATE_NG));
	if(success == true){
		mess.sendCode(char(Protocol::ANS_ACK));
	} else{
		mess.sendCode(char(Protocol::ANS_NAK));
		mess.sendCode(char(Protocol::ERR_NG_ALREADY_EXISTS));
	}
	mess.sendCode(char(Protocol::ANS_END));

}

void deleteNewsGroups(MessageHandler& mess, Database_interface& database){

    /*
	COM_DELETE_NG num_p COM_END
	ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
	*/ 

	int id = mess.recvIntParameter();
	if (mess.recvCode() != char(Protocol::COM_END)){
		//Throw error
		std::cerr << "Protocol violation in delete NG" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
	} else {
    	bool success = database.delete_NG(id);
    	mess.sendCode(char(Protocol::ANS_DELETE_NG));
    	if(success == true){
    		mess.sendCode(char(Protocol::ANS_ACK));
    	} else{
    		mess.sendCode(char(Protocol::ANS_NAK));
    		mess.sendCode(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    	}
    	mess.sendCode(char(Protocol::ANS_END));
    }

}

void listArticle(MessageHandler& mess, Database_interface& database){

    /*
	COM_LIST_ART num_p COM_END
	ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
	*/

	int id = mess.recvIntParameter();
	if (mess.recvCode() != char(Protocol::COM_END)){
		//Throw error
		std::cerr << "Protocol violation in list articles" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
	} else {
    	mess.sendCode(char(Protocol::ANS_LIST_ART));
    	try{
    		auto list_of_articles = database.list_articles(id);

    		mess.sendCode(char(Protocol::ANS_ACK));
    		mess.sendIntParameter(list_of_articles.size());
			for(auto it = list_of_articles.begin(); it != list_of_articles.end(); ++it){
				mess.sendIntParameter((*it).first);
				mess.sendStringParameter((*it).second);
			}
    	} catch(const std::runtime_error& e){
    		mess.sendCode(char(Protocol::ANS_NAK));
    		mess.sendCode(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    	}
    	mess.sendCode(char(Protocol::ANS_END));
    }

}

void createArticle(MessageHandler& mess, Database_interface& database){
    
    /*
	COM_CREATE_ART num_p string_p string_p string_p COM_END
	ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
	*/

	int id_NG = mess.recvIntParameter();
	std::string title = mess.recvStringParameter();
	std::string author = mess.recvStringParameter();
	std::string text = mess.recvStringParameter();
	if (mess.recvCode() != char(Protocol::COM_END)){
		//throw error
		std::cerr << "Protocol violation in create article" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
	} else{
    	bool success = database.create_article(id_NG, title, author, text);
    	mess.sendCode(char(Protocol::ANS_CREATE_ART));
    	if (success == true){
    		mess.sendCode(char(Protocol::ANS_ACK));
    	} else{
    		mess.sendCode(char(Protocol::ANS_NAK));
    		mess.sendCode(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    	}
    	mess.sendCode(char(Protocol::ANS_END));
    }

}

void deleteArticle(MessageHandler& mess, Database_interface& database){

    /*
	COM_DELETE_ART num_p num_p COM_END
	ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
	*/

	int id_NG = mess.recvIntParameter();
	int id_art = mess.recvIntParameter();
	if (mess.recvCode() != char(Protocol::COM_END)){
		//throw error
		std::cerr << "Protocol violation in delete article" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
	} else {
    	mess.sendCode(char(Protocol::ANS_DELETE_ART));
    	try{
    		database.delete_article(id_NG, id_art);
    		mess.sendCode(char(Protocol::ANS_ACK));

    	} catch(std::runtime_error& e){
    		mess.sendCode(char(Protocol::ANS_NAK));
    		std::string error = e.what();
    		if (error == "no such NG"){
    			mess.sendCode(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    		} else if(error == "no such article"){
    			mess.sendCode(char(Protocol::ERR_ART_DOES_NOT_EXIST));
    		} else{
    			std::cout << "Error unknown error." << std::endl;
    		}
    	}
    	mess.sendCode(char(Protocol::ANS_END));
    }

}

void showArticle(MessageHandler& mess, Database_interface& database){

    /*
	COM_GET_ART num_p num_p COM_END
	ANS_GET_ART [ANS_ACK string_p string_p string_p | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
	*/

	int id_NG = mess.recvIntParameter();
	int id_art = mess.recvIntParameter();
	if (mess.recvCode() != char(Protocol::COM_END)){
		//throw error
		std::cerr << "Protocol violation in get article" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
	} else {
    	mess.sendCode(char(Protocol::ANS_GET_ART));
    	try{
    		std::vector<std::string> article = database.get_article(id_NG, id_art);
    		mess.sendCode(char(Protocol::ANS_ACK));
    		for(auto it = article.begin(); it != article.end(); ++it){
    			mess.sendStringParameter(*it);
    		} 

    	} catch(std::runtime_error& e){
    		mess.sendCode(char(Protocol::ANS_NAK));
            std::string what = e.what();
    		if (what == "no such NG"){
    			mess.sendCode(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    		} else{
    			mess.sendCode(char(Protocol::ERR_ART_DOES_NOT_EXIST));
    		}
    	}
    	mess.sendCode(char(Protocol::ANS_END));
    }
    
}

void process_request(MessageHandler& mess, Database_interface& database){
	char nbr = mess.recvCode();
	//std::cout << "case read"<< nbr  << " " << int(char(Protocol::COM_CREATE_NG)) << std::endl;
	// switch case för vilket command det är
	switch(nbr){
	case char(Protocol::COM_LIST_NG):
        listNewsGroups(mess,database);
		break;

	case char(Protocol::COM_CREATE_NG):{
		createNewsGroups(mess,database);
		break;
	}
    case char(Protocol::COM_DELETE_NG):{
    	deleteNewsGroups(mess,database);
    	break;
    }
    case char(Protocol::COM_LIST_ART):{
    	listArticle(mess,database);
    	break;
    }
    case char(Protocol::COM_CREATE_ART):{
    	createArticle(mess,database);
    	break;
    }
    case char(Protocol::COM_DELETE_ART):{
    	deleteArticle(mess,database);
    	break;
    }
    case char(Protocol::COM_GET_ART):{
    	showArticle(mess,database);
    	break;
    }
    case char(Protocol::COM_END):{
    	//throw some error
    	std::cerr << "recieved unexpected COM_END" << std::endl;
		mess.sendCode(char(Protocol::ANS_END));
    	break;
    }
	default:{
		std::cerr << "no case! wrong integer sent from client!!!" << std::endl;
        mess.sendCode(char(Protocol::ANS_END));
	}
	}
}

void running_server(Server& server, Database_interface& database) {
    auto conn = server.waitForActivity();
    if (conn != nullptr) {
        try {
            MessageHandler mess{};
            mess.setConnection(conn);
            process_request(mess, database);
        } catch (ConnectionClosedException&) {
            server.deregisterConnection(conn);
            cout << "Client closed connection" << endl;
        }
    } else {
        conn = std::make_shared<Connection>();
        server.registerConnection(conn);
        cout << "New client connects" << endl;
    }
}

int main(int argc, char* argv[]){

    std::shared_ptr<Database_interface> database;

    auto server = init(argc, argv, database);

    while (true) {
        running_server(server, *database);
    }
    return 0;
}