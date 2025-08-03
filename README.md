# my_teams

## Description
This project is to make a server running on your local machine and a client that can connect to this server. The client can then login and send messages to other clients. It demonstrates the use of `select`, `send`, `read`, `bind` and `listen` functions.

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

## Program commands

Display help:

    /help
Login with a username:

    /login <username> #this will return you an uuid
Send message to someone:

    /send <uuid> <message>
See all users information:

    /users
See one user information:

    /user <uuid>
See conversation with a user:

    /conv <uuid>
Logout:

    /logout
Quit the program:

    /quit


## SonarQube

### Create SonarQube

# Create pod
podman pod create --name sonar -p 9000:9000

# Start PostgreSQL
podman run -d \
  --name sonarqube-postgres \
  --pod sonar \
  -e POSTGRES_USER=sonar \
  -e POSTGRES_PASSWORD=sonar \
  -e POSTGRES_DB=sonarqube \
  -v pg_data:/var/lib/postgresql/data \
  docker.io/postgres:15

# Give PostgreSQL a few seconds to start

# Start SonarQube
podman run -d \
  --name sonarqube \
  --pod sonar \
  -e SONAR_JDBC_URL=jdbc:postgresql://localhost:5432/sonarqube \
  -e SONAR_JDBC_USERNAME=sonar \
  -e SONAR_JDBC_PASSWORD=sonar \
  -v sonarqube_data:/opt/sonarqube/data \
  -v sonarqube_extensions:/opt/sonarqube/extensions \
  -v sonarqube_logs:/opt/sonarqube/logs \
  docker.io/sonarqube:community


Look at http://localhost:9000/ and use admin / admin to login

Sinon utilisez: https://sonarcloud.io/projects