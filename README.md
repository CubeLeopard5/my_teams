# my_teams

## Requirements
You need:
- **gcc** to compile with the makefile
- **libuuid-devel**  to use this program
- **criterion** to run the tests

## Compilation
Use `make` to compile the program with the Makefile. This will give you 3 binaries:

- myteams_server
- myteams_cli
- run_tests
 
You can add to the `make` command the target of compilation:

    make server
    make client
    make tests

Use `make fclean` to remove all .o files and binaries.

## Usage
To run the server:

    ./myteams_server
This will make the server running on `127.0.0.1` and to use the default port `4000`.
You can add the option `-p` or `--port` to change the port number. 

To run the client:

    ./myteams_cli <host> <port number>
Choose the host and port number of an existing myteams_server running instance.

To run the tests:

    ./run_tests
