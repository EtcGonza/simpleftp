// Gonzalo Etchegaray Xavier
// COMISION 1

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>
#include <err.h>

#include <netinet/in.h>
#include <sys/socket.h>

#include <ctype.h>
#include <signal.h>

#define BACKLOG 10
#define BUFSIZE 512
#define CMDSIZE 4
#define PARSIZE 100

#define MSG_220 "220 srvFtp version 1.0\r\n"
#define MSG_331 "331 Password required for %s\r\n"
#define MSG_230 "230 User %s logged in\r\n"
#define MSG_530 "530 Login incorrect\r\n"
#define MSG_221 "221 Goodbye\r\n"
#define MSG_550 "550 %s: no such file or directory\r\n"
#define MSG_299 "299 File %s size %ld bytes\r\n"
#define MSG_226 "226 Transfer complete\r\n"

/**
 * function: receive the commands from the client
 * sd: socket descriptor
 * operation: \0 if you want to know the operation received
 *            OP if you want to check an especific operation
 *            ex: recv_cmd(sd, "USER", param)
 * param: parameters for the operation involve
 * return: only usefull if you want to check an operation
 *         ex: for login you need the seq USER PASS
 *             you can check if you receive first USER
 *             and then check if you receive PASS
 **/
bool recv_cmd(int sd, char *operation, char *param) {
    char buffer[BUFSIZE], *token;
    int recv_s;

    // receive the command in the buffer and check for errors

    // expunge the terminator characters from the buffer

    // complex parsing of the buffer
    // extract command receive in operation if not set \0
    // extract parameters of the operation in param if it needed
    
    return true;
}

/**
 * function: send answer to the client
 * sd: file descriptor
 * message: formatting string in printf format
 * ...: variable arguments for economics of formats
 * return: true if not problem arise or else
 * notes: the MSG_x have preformated for these use
 **/
bool send_ans(int sd, char *message, ...){
    char buffer[BUFSIZE];

    va_list args;
    va_start(args, message);

    vsprintf(buffer, message, args);
    va_end(args);
    // send answer preformated and check errors
    bytes_sent = send(sd, buffer, strlen(buffer), 0);
    if(bytes_sent == -1) {
        warn("Error al enviar sd: %d | %s\n", sd, buffer);
        return false;
    }
    return true;
}

/**
 * function: RETR operation
 * sd: socket descriptor
 * file_path: name of the RETR file
 **/

void retr(int sd, char *file_path) {
    FILE *file;    
    int bread;
    long fsize;
    char buffer[BUFSIZE];

    // check if file exists if not inform error to client

    // send a success message with the file length

    // important delay for avoid problems with buffer size
    sleep(1);

    // send the file

    // close the file

    // send a completed transfer message
}
/**
 * funcion: check valid credentials in ftpusers file
 * user: login user name
 * pass: user password
 * return: true if found or false if not
 **/
bool check_credentials(char *user, char *pass) {
    FILE *file;
    char *path = "./ftpusers", *line = NULL, cred[100];
    size_t len = 0;
    bool found = false;

    // make the credential string
    strcpy(cred, user);
    strcat(cred, ":");
    strcat(cred, pass);
    strcat(cred, "\n");
    
    // check if ftpusers file it's present
    file = fopen(path, "r");
    if (file == NULL) {
        printf(MSG_550);
    }
    
    // search for credential string
    line = (char *)malloc(sizeof(char)*100);
    
    while(feof(file) == 0) {
        fgets(line, 100, file);
    }
    if (strcmp(file, line) == 0) {
        found = true;
    } 
    
    // close file and release any pointes if necessary
    fclose(file);
    
    // return search status
    return found;
}

/**
 * function: login process management
 * sd: socket descriptor
 * return: true if login is succesfully, false if not
 **/
bool authenticate(int sd) {
    char user[PARSIZE], pass[PARSIZE];

    // wait to receive USER action

    // ask for password

    // wait to receive PASS action

    // if credentials don't check denied login

    // confirm login
}

/**
 *  function: execute all commands (RETR|QUIT)
 *  sd: socket descriptor
 **/

void operate(int sd) {
    char op[CMDSIZE], param[PARSIZE];

    while (true) {
        op[0] = param[0] = '\0';
        // check for commands send by the client if not inform and exit


        if (strcmp(op, "RETR") == 0) {
            retr(sd, param);
        } else if (strcmp(op, "QUIT") == 0) {
            // send goodbye and close connection




            break;
        } else {
            // invalid command
            // furute use
        }
    }
}

/**
 * Run with
 *         ./mysrv <SERVER_PORT>
 **/
int main (int argc, char *argv[]) {
    // arguments checking
    if (argc != 2) {
        printf("Usando el:%s <SERVER_PORT>", argv[0]);
        exit(1);
    }

    // reserve sockets and variables space
    int sock, fd;
    struct sockaddr_in address;
    struct sockaddr_in their_addr;
    int size;

    address.sin_family = AF_INET;         
    address.sin_port = htons(*argv[1]);   
    address.sin_addr.s_addr = INADDR_ANY; 
    memset(&(address.sin_zero), '\0', 8); 

    // create server socket and check errors
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error en el socket.");
        exit(1);
    }
    
    // bind master socket and check errors
    if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr)) == -1) {
        perror("Error en el bind");
        exit(1);
    }

    // make it listen
    if (listen(sock, BACKLOG) == -1) {
        perror("Error en el listen");
        exit(1);
    }

    // main loop
    while (true) {
        // accept connectiones sequentially and check errors
        size = sizeof(struct sockaddr_in);
        if ((fd = accept(sock, (struct sockaddr *)&their_addr,(socklen_t *)&size)) == -1) {
            perror("Error al aceptar la conexion.");
            continue;
        }

        printf("Se recibio una conexion desde %s\n", inet_ntoa(their_addr.sin_addr));
        
        // send hello
        send_ans(fd, MSG_220);

        // operate only if authenticate is true
        if(!authenticate(fd)) close(fd);
            else operate(fd);
    }

    // close server socket
    close(sock);
    
    return 0;
}
