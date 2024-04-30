/* myserver.cc: sample server program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"
#include "database_interface.h"
#include "inmemorydatabase.h"
#include "diskdatabase.h"
#include "protocol.h"
#include "protocolviolationexception.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

/*
 * Read an int from a client.
 */
int readInt(const std::shared_ptr<Connection>& conn){
	unsigned char byte1 = conn->read();
    unsigned char byte2 = conn->read();
    unsigned char byte3 = conn->read();
    unsigned char byte4 = conn->read();
    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

/*
 * Read an num_p from a client.
 */
int readNumber(const std::shared_ptr<Connection>& conn)
{
    if(conn->read() != char(Protocol::PAR_NUM)){
    	std::cerr << "expected PAR_NUM" << std::endl;
    }
    return readInt(conn); 
}

/*
 * Read a string from a client.
 */
std::string readString(const std::shared_ptr<Connection>& conn)
{
	char c = conn->read();
	if(not (c==char(Protocol::PAR_STRING))){
		std::cerr << "expected PAR_STRING" << std::endl;
	}
	int N = readInt(conn);
	std::string s{};
    for(int i=0; i<N; ++i) {
        char c = conn->read();
    	s.push_back(c);
    }
    return s;
}

/*
 * Write an integer to a client.
 */

void writeInt(const std::shared_ptr<Connection>& conn, int nbr){
	unsigned char byte1 = nbr >> 24;
	unsigned char byte2 = nbr >> 16;
	unsigned char byte3 = nbr >> 8;
	unsigned char byte4 = nbr >> 0;
	conn->write(byte1);
	conn->write(byte2);
	conn->write(byte3);
	conn->write(byte4);
}

/*
 * Send num_p to a client.
 */

void writeNumber(const std::shared_ptr<Connection>& conn, int nbr)
{
	conn->write(char(Protocol::PAR_NUM));

	writeInt(conn, nbr);
}

/*
 * Send a string_p to a client.
 */

void writeString(const std::shared_ptr<Connection>& conn, const string& s)
{
	conn->write(char(Protocol::PAR_STRING));
	writeInt(conn, s.size());
    for (char c : s) {
        conn->write(c);
    }
}

Server init(int argc, char* argv[])
{
        if (argc != 3) {
                cerr << "Usage: myserver port-number database-type(1=inmemory,2=disk)" << endl;
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
        return server;
}

void listNewsGroups(std::shared_ptr<Connection>& conn, Database_interface& database){

    /*
	COM_LIST_NG COM_END
	ANS_LIST_NG num_p [num_p string_p]* ANS_END
	*/
	
	if (conn->read() == char(Protocol::COM_END)){
		auto list_of_newsgroups = database.list_NG();
		conn->write(char(Protocol::ANS_LIST_NG));
		writeNumber(conn, list_of_newsgroups.size());
		for(auto it = list_of_newsgroups.begin(); it != list_of_newsgroups.end(); ++it){
			writeNumber(conn, (*it).first);
			writeString(conn, (*it).second);
		}
		conn->write(char(Protocol::ANS_END));
	} else{
		//throw some error
		std::cerr << "Protocol violation in list NGs" << std::endl;
		conn->write(char(Protocol::ANS_END));
	}

}

void createNewsGroups(std::shared_ptr<Connection>& conn, Database_interface& database){

    /*
	COM_CREATE_NG string_p COM_END
	ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
	*/
	bool success = database.create_NG(readString(conn));
	if (conn->read() != int(char(Protocol::COM_END))){
		//Throw error;
		std::cerr << "Protocol violation in create NG" << std::endl;
		conn->write(char(Protocol::ANS_END));
	}
	conn->write(char(Protocol::ANS_CREATE_NG));
	if(success == true){
		conn->write(char(Protocol::ANS_ACK));
	} else{
		conn->write(char(Protocol::ANS_NAK));
		conn->write(char(Protocol::ERR_NG_ALREADY_EXISTS));
	}
	conn->write(char(Protocol::ANS_END));

}

void deleteNewsGroups(std::shared_ptr<Connection>& conn, Database_interface& database){

    /*
	COM_DELETE_NG num_p COM_END
	ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
	*/ 

	int id = readNumber(conn);
	if (conn->read() != char(Protocol::COM_END)){
		//Throw error
		std::cerr << "Protocol violation in delete NG" << std::endl;
		conn->write(char(Protocol::ANS_END));
	} else {
    	bool success = database.delete_NG(id);
    	conn->write(char(Protocol::ANS_DELETE_NG));
    	if(success == true){
    		conn->write(char(Protocol::ANS_ACK));
    	} else{
    		conn->write(char(Protocol::ANS_NAK));
    		conn->write(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    	}
    	conn->write(char(Protocol::ANS_END));
    }

}

void listArticle(std::shared_ptr<Connection>& conn, Database_interface& database){

    /*
	COM_LIST_ART num_p COM_END
	ANS_LIST_ART [ANS_ACK num_p [num_p string_p]* | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
	*/

	int id = readNumber(conn);
	if (conn->read() != char(Protocol::COM_END)){
		//Throw error
		std::cerr << "Protocol violation in list articles" << std::endl;
		conn->write(char(Protocol::ANS_END));
	} else {
    	conn->write(char(Protocol::ANS_LIST_ART));
    	try{
    		auto list_of_articles = database.list_articles(id);

    		conn->write(char(Protocol::ANS_ACK));
    		writeNumber(conn, list_of_articles.size());
			for(auto it = list_of_articles.begin(); it != list_of_articles.end(); ++it){
				writeNumber(conn, (*it).first);
				writeString(conn, (*it).second);
			}
    	} catch(const std::runtime_error& e){
    		conn->write(char(Protocol::ANS_NAK));
    		conn->write(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    	}
    	conn->write(char(Protocol::ANS_END));
    }

}

void createArticle(std::shared_ptr<Connection>& conn, Database_interface& database){
    
    /*
	COM_CREATE_ART num_p string_p string_p string_p COM_END
	ANS_CREATE_ART [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
	*/

	int id_NG = readNumber(conn);
	std::string title = readString(conn);
	std::string author = readString(conn);
	std::string text = readString(conn);
	if (conn->read() != char(Protocol::COM_END)){
		//throw error
		std::cerr << "Protocol violation in create article" << std::endl;
		conn->write(char(Protocol::ANS_END));
	} else{
    	bool success = database.create_article(id_NG, title, author, text);
    	conn->write(char(Protocol::ANS_CREATE_ART));
    	if (success == true){
    		conn->write(char(Protocol::ANS_ACK));
    	} else{
    		conn->write(char(Protocol::ANS_NAK));
    		conn->write(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    	}
    	conn->write(char(Protocol::ANS_END));
    }

}

void deleteArticle(std::shared_ptr<Connection>& conn, Database_interface& database){

    /*
	COM_DELETE_ART num_p num_p COM_END
	ANS_DELETE_ART [ANS_ACK | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
	*/

	int id_NG = readNumber(conn);
	int id_art = readNumber(conn);
	if (conn->read() != char(Protocol::COM_END)){
		//throw error
		std::cerr << "Protocol violation in delete article" << std::endl;
		conn->write(char(Protocol::ANS_END));
	} else {
    	conn->write(char(Protocol::ANS_DELETE_ART));
    	try{
    		database.delete_article(id_NG, id_art);
    		conn->write(char(Protocol::ANS_ACK));

    	} catch(std::runtime_error& e){
    		conn->write(char(Protocol::ANS_NAK));
    		std::string error = e.what();
    		if (error == "no such NG"){
    			conn->write(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    		} else if(error == "no such article"){
    			conn->write(char(Protocol::ERR_ART_DOES_NOT_EXIST));
    		} else{
    			std::cout << "Error unknown error." << std::endl;
    		}
    	}
    	conn->write(char(Protocol::ANS_END));
    }

}

void showArticle(std::shared_ptr<Connection>& conn, Database_interface& database){

    /*
	COM_GET_ART num_p num_p COM_END
	ANS_GET_ART [ANS_ACK string_p string_p string_p | ANS_NAK [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]] ANS_END
	*/

	int id_NG = readNumber(conn);
	int id_art = readNumber(conn);
	if (conn->read() != char(Protocol::COM_END)){
		//throw error
		std::cerr << "Protocol violation in get article" << std::endl;
		conn->write(char(Protocol::ANS_END));
	} else {
    	conn->write(char(Protocol::ANS_GET_ART));
    	try{
    		std::vector<std::string> article = database.get_article(id_NG, id_art);
    		conn->write(char(Protocol::ANS_ACK));
    		for(auto it = article.begin(); it != article.end(); ++it){
    			writeString(conn, (*it));
    		} 

    	} catch(std::runtime_error& e){
    		conn->write(char(Protocol::ANS_NAK));
            std::string what = e.what();
    		if (what == "no such NG"){
    			conn->write(char(Protocol::ERR_NG_DOES_NOT_EXIST));
    		} else{
    			conn->write(char(Protocol::ERR_ART_DOES_NOT_EXIST));
    		}
    	}
    	conn->write(char(Protocol::ANS_END));
    }
    
}

void process_request(std::shared_ptr<Connection>& conn, Database_interface& database){
	char nbr = conn->read();
	//std::cout << "case read"<< nbr  << " " << int(char(Protocol::COM_CREATE_NG)) << std::endl;
	// switch case för vilket command det är
	switch(nbr){
	case char(Protocol::COM_LIST_NG):
        listNewsGroups(conn,database);
		break;

	case char(Protocol::COM_CREATE_NG):{
		createNewsGroups(conn,database);
		break;
	}
    case char(Protocol::COM_DELETE_NG):{
    	deleteNewsGroups(conn,database);
    	break;
    }
    case char(Protocol::COM_LIST_ART):{
    	listArticle(conn,database);
    	break;
    }
    case char(Protocol::COM_CREATE_ART):{
    	createArticle(conn,database);
    	break;
    }
    case char(Protocol::COM_DELETE_ART):{
    	deleteArticle(conn,database);
    	break;
    }
    case char(Protocol::COM_GET_ART):{
    	showArticle(conn,database);
    	break;
    }
    case char(Protocol::COM_END):{
    	//throw some error
    	std::cerr << "recieved unexpected COM_END" << std::endl;
		conn->write(char(Protocol::ANS_END));
    	break;
    }
	default:{
		std::cerr << "no case! wrong integer sent from client!!!" << std::endl;
	}
	}
}

void serve_one(Server& server, Database_interface& database) {
    auto conn = server.waitForActivity();
    if (conn != nullptr) {
        try {
            process_request(conn, database);
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
	
    //int databasetype;
    // try
    // {
    //     databasetype = std::stoi(argv[2]);
    // }
    // catch(const std::exception& e)
    // {
    //     cerr << "Wrong format for databasetype number. " << e.what() << endl;
    //     exit(2);
    // }
    
    InMemoryDatabase database{};

    // Database_interface database;
    // database = InMemoryDatabase{};

    // if(databasetype == 1){
	//     database = InMemoryDatabase{};
    // }else if(databasetype == 2){
    //     database = DiskDatabase{};
    // }else{
    //     cerr << "Databasetype number must be 1 or 2." << endl;
    //     exit(2);
    // }

    auto server = init(argc, argv);

    while (true) {
        serve_one(server, database);
    }
    return 0;
}