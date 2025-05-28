#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);    

    char IP[] = "127.0.0.1";
    int Port = 8888;
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    serv_addr.sin_port = htons(Port);

    bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(sockfd, SOMAXCONN);

    printf("  App Running at:\n");
    printf("  -Network:IP=[%s] Port=[%d]\n\n", IP, Port);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_len = sizeof(clnt_addr);
    bzero(&clnt_addr, sizeof(clnt_addr));
    
    int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);

    printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

    char buffer[1024] = { 0 };
    ssize_t valread = read(clnt_sockfd, buffer,
                   sizeof(buffer) - 1); // subtract 1 for the null, terminator at the end
    printf("message from client fd %d: %s\n", clnt_sockfd, buffer);
    
    char hello[] = "Hello from server";
    write(clnt_sockfd, hello, strlen(hello));
    printf("Hello message sent\n");

    // closing the connected socket
    close(clnt_sockfd);
    // closing the listening socket
    close(sockfd);
    return 0;
}
