#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));    
    
    char buf[1024];
    bzero(&buf, sizeof(buf));
    fgets(buf, sizeof(buf), stdin);
    ssize_t write_bytes = write(sockfd, buf, sizeof(buf));
    
    bzero(&buf, sizeof(buf));
    ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
    printf("message from server: %s\n", buf);
            
    return 0;
}
