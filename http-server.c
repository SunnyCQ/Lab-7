#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h> //check if allowed to use

static void die(const char *s) { perror(s); exit(1);}

int main(int argc, char **argv){
    //(1) check argv arguments
    if(argc != 5){
        fprintf(stderr, "usage: %s <server_port> <web_root> <mdb-lookup-host> <mdb-lookup-port>\n", argv[0]);
        exit(1);
    }

    //(2) obtain server port, web root, mdb-lookup-host, and mdb-lookup-port
    unsigned short server_port = atoi(argv[1]); //server_port (i.e 8888)
    const char *web_root = argv[2]; //web_root (i.e /home/jae/html/cs3157)
    const char *mdb-lookup-host = argv[3]; //mdb-lookup-host IP (i.e 127.0.0.1)
    unsigned char *mdb-lookup-port = atoi(argv[4]); //mdb-lookup-port (i.e 9999)

    //(3) create listening socket (server socket)
    int servsock;
    if ((servsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket failed");

    //(4) construct local addres structure
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //listen from any network interface(so any browser can access)
    servaddr.sin_port = htons(server_port);

    //(5) Bind servsock to local address
    if(bind(servsock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 )
        die("bind failed");

    //(6) make servsock listen for conections
    if(listen(servsock, 1) < 0) //handle only 1 client at a time
        die("listen failed");

    //(7) setup client socket
    int clntsock;
    socklen_t clntlen;
    struct sockaddr_in clntaddr;

    //(8) create while loop to manage clients
    while(1){
        fprintf(stderr, "waiting for client...");
        clntlen = sizeof(clntaddr);
        //(9) accept clients
        if((clntsock = accept(servsock, (struct sockaddr *) &clntaddr, &clntlen)) < 0)
            die("accept failed");
        //(10) open client socket as readable file pointer
        FILE *clnt_input = fdopen(clntsock, "r");
        if(clnt_input == NULL)
            die("fdopen failed");

        //(11) Get info about (1 single) GET request
        char buf[4096];
        if((fgets(buf, sizeof(buf), input)) == NULL)
            die("getting first line (GET REQUEST) failed");
        //char req_type[1024];
        //char file_path[1024];
        //char http_ver[1024];
        //sscanf(buf, "%s %s %s", req_type, file_path, http_ver); //Parse GET request for information
        //(12) check if GET request is valid
        char *token_separators = "\t \r\n"; // tab, space, new line 
        char *req_type = strtok(requestLine, token_separators); 
        char *requestURI = strtok(NULL, token_separators);
        char *httpVersion = strtok(NULL, token_separators);

        if(strcmp(req_type, "GET") != 0){
            fprintf(stderr, "Request type mismatch: %s", req_type); //DONT DIE
        }else if((strcmp(httpVersion, "HTTP/1.0") !=0) && (strcmp(httpVersion, "HTTP/1.1")) != 0){
            fprintf(stderr, "HTTP version mismatch: %s", httpVersion);
        }






        while((fgets(buf, sizeof(buf), input) != NULL)){
            while((fgets(buf, sizeof(headers), clnt_input) != NULL) && (strcmp(
        }

        //(10) print out information on client (i.e 128.59.177.106 "GET /tng/images/crew.jpg HTTP/1.1" 200 OK)
        fprintf(stderr, "%s\n", inet_ntoa(clntaddr.sin_addr)); //inet_ntoa converts IP address to readable format

    }


    return 0;
}

    



