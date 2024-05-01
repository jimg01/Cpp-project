## Client and Server Project in Cpp

This is a client-server program where you have a server where multiple clients can connect to.
The server consists of a database where "NewsGroups" and "Articles can be stored.
The database is eighter a inmemory-database, witch will be deleted everytime you close the server, and a disk-database, witch will save it content in directorys and .txt files and will remain after server shutdown.
There can be multiple NewsGroups, and every NesGroup can have multiple Articles in them.
An Article consiste of a "Name", an "Author" and the "body text".
The client consists of a text-based user-interface in the terminal. All input and outputs are made in the termianl.
When you start the client an optionlist will apere from where you can create, list and delete NewsGroups and Articles. You will be directed with prompts from the client on how to use the client. 


## Building with make

`make` in the "axisbrjo" directory complies the client and the server in the "src" directory.
`make install` complies the programs and copys them to the "bin" directory.

For cleaning, use `make clean` and `make distclean`.

## Running the client and the server

To run the client and the server, open two terminal windows.

In the first one, start the server with `ourserver <port> <database-type>`, e.g.,

-
`bin/myserver 1234 1`
-

This will start a server with a inmemory-database, (database-type = 1(inmemory), 2(disk)).
If you start a diskdatabase a database directory will be created where the database is stored.
To remove/reset the diskdatabase, just remove the directory "database" before starting the server.

In the other one, start the client with `client <server> <port>`, e.g.,

-
`bin/myclient localhost 1234`
-