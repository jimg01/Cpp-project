## Client and Server Project in Cpp

This is a client-server program where you have a server that multiple clients can connect to.
The server consists of a database where "NewsGroups" and "Articles" can be stored.
The database is either a inmemory-database, which will be deleted everytime you close the server, or a disk-database, which will save its content in directories and .txt files and will remain after server shutdown.
There can be multiple NewsGroups, and every NewsGroup can have multiple Articles in them.
An Article consists of a "Name", an "Author" and the "body text".

The client consists of a text-based user-interface in the terminal. All inputs and outputs are made in the terminal.
When you start the client an optionlist will appear from where you can create, list and delete NewsGroups and Articles. You will be directed with prompts from the client on how to use the client. 


## Building with make

`make` in the "axisbrjo" directory compiles the client and the server in the "src" directory.
`make install` compiles the programs and copies the executables to the "bin" directory.

For cleaning, use `make clean` and `make distclean`.

## Running the client and the server

To run the client and the server, open two terminal windows.

In the first one, start the server with `ourserver <port> <database-type>`, e.g.,

-
`bin/ourserver 1234 1`
-

This will start a server with an inmemory-database, (database-type = 1(inmemory), 2(disk)).
If you start a diskdatabase a database directory will be created where the server was started from.
To remove/reset the diskdatabase, just remove the directory "database" before starting the server.

In the other terminal, start the client with `client <server> <port>`, e.g.,

-
`bin/client localhost 1234`
-
