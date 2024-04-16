/* myserver.cc: sample server program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"
#include "database_interface.h"
#include "../include/protocol.h"

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
 * Read an integer from a client.
 */
int readNumber(const std::shared_ptr<Connection>& conn)
{
        unsigned char byte1 = conn->read();
        unsigned char byte2 = conn->read();
        unsigned char byte3 = conn->read();
        unsigned char byte4 = conn->read();
        return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

/*
 * Read a string from a client.
 */
std::string readString(const std::shared_ptr<Connection>& conn)
{
	std::string s{};
	char c = conn->read()
    while (c != '$') {
    	s.pushback(c);
        char c = conn->read();
    }
    return s;
}

/*
 * Write an integer to a client.
 */
void writeNumber(const std::shared_ptr<Connection>& conn, int nbr)
{
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
 * Send a string to a client.
 */
void writeString(const std::shared_ptr<Connection>& conn, const string& s)
{
        for (char c : s) {
                conn->write(c);
        }
        conn->write('$');
}

Server init(int argc, char* argv[])
{
        if (argc != 2) {
                cerr << "Usage: myserver port-number" << endl;
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

void process_request(std::shared_ptr<Connection>& conn)
{
    /*
    int    nbr = readNumber(conn);
    string result;
    if (nbr > 0) {
            result = "positive";
    } else if (nbr == 0) {
            result = "zero";
    } else {
            result = "negative";
    }
    writeString(conn, result);
    */
	
	int nbr = readNumber(conn);
	// switch case för vilket command det är
	switch(nbr){
	case COM_LIST_NG:
		/*
		COM_LIST_NG COM_END
		ANS_LIST_NG num_p [num_p string_p]* ANS_END
		*/
		if (readNumber(conn) == COM_END){
			list_of_newsgroups = database.list_NG();
			writeNumber(conn, ANS_LIST_NG);
			writeNumber(conn, list_of_newsgroups.size());
			for(auto it = list_of_newsgroups.begin(); it != list_of_newsgroups.end(); ++it){
				writeNumber(conn, (*it).first);
				writeString(conn, (*it).second);
			}
			writeNumber(conn, ANS_END);
		} else{
			//throw some error
		}
		break;

	case COM_CREATE_NG:
		/*
		COM_CREATE_NG string_p COM_END
		ANS_CREATE_NG [ANS_ACK | ANS_NAK ERR_NG_ALREADY_EXISTS] ANS_END
		*/
		bool success = database.create_NG(readString(conn));
		if (readNumber(conn) != COM_END){
			//Throw error;
		}
		writeNumber(conn, ANS_CREATE_NG);
		if(success == true){
			writeNumber(conn, ANS_ACK);
		} else{
			writeNumber(conn, ANS_NAK);
			writeNumber(conn, ERR_NG_ALREADY_EXISTS);
		}
		writeNumber(conn, ANS_END);
		break;

    case COM_DELETE_NG:
    	/*
		COM_DELETE_NG num_p COM_END
		ANS_DELETE_NG [ANS_ACK | ANS_NAK ERR_NG_DOES_NOT_EXIST] ANS_END
    	*/ 
    	int id = readNumber(conn);
    	if (readNumber(conn) != COM_END){
    		//Throw error
    	}
    	bool success = database.delete_NG(id);
    	if(success == true){
    		writeNumber(conn, ANS_ACK);
    	} else{
    		writeNumber(conn, ANS_NAK);
    		writeNumber(conn, ERR_NG_DOES_NOT_EXIST);
    	}
    	writeNumber(conn, ANS_END);
    	break;



    case COM_LIST_ART:
    case COM_CREATE_ART:
    case COM_DELETE_ART:
    case COM_GET_ART:
    case COM_END:
	}
	if (nbr == 1) {
		//result = database_interface"." getlist
	}
	

    //writeString(conn, result);

}

void serve_one(Server& server)
{
        auto conn = server.waitForActivity();
        if (conn != nullptr) {
                try {
                    process_request(conn);
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

int main(int argc, char* argv[])
{

	//create empty database type 1
	InMemoryDataBase database{};

    auto server = init(argc, argv);

    while (true) {
        serve_one(server);
    }
    return 0;
}