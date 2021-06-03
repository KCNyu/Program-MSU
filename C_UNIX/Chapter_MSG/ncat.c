#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);

int main(int argc, char ** argv) {
    if (argc < 3) {
        fprintf(stderr, "Not enough args, should be: ncat host port\n");
        return 1; 
    }
    char * host = argv[1];
    char * port = argv[2];
    struct addrinfo * ad;
    struct addrinfo hints = {};
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = 0;

    int ret = getaddrinfo(host, port, &hints, &ad);
    if (ret != 0) {
        fprintf(stderr, "getaddr error: %s\n", gai_strerror(ret));
        return 1; 
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket error ");
        return 1; 
    }
    int conn = connect(sock, ad->ai_addr, ad->ai_addrlen);
    if (conn == -1) {
        perror("Connect error ");
        return 1; 
    }
    FILE * sockr;
    int fdr = dup(sock);
    sockr = fdopen(fdr, "r");
    FILE * sockw;
    sockw = fdopen(sock, "w");
    
    if (sockr == NULL || sockw == NULL) {
        fprintf(stderr, "fdopen error\n");
        return 1; 
    }
    
    const int BUF_SIZE = 1024;
    char buf[BUF_SIZE];
    int x;
    char c;
    
    freeaddrinfo(ad);
    pid_t son = fork();
    if (son == -1) {
        fprintf(stderr, "fork error\n");
        return 1; 
    }
    if (son == 0) {
        // son
        fclose(sockw); 
        while ((x = getc(sockr)) != EOF) {
            putchar(x); 
        }
        fclose(sockr); 
        return 0;
    } else {
        // parent
        fclose(sockr); 
        while ((x = getchar()) != EOF) {
            fputc(x, sockw);
        } 
        fclose(sockw); 
        wait(NULL);
    }
    return 0;
}

