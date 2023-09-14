#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>

#include "../../include.h"


int main(int argc, char const *argv[])
{
    errno = 0;
    
    int serv_sock_d, client_sock_d, client_addr_len, result, result2;
    struct sockaddr_in serv_addr = { 0 }, client_addr = { 0 };
    char recv_buf[80] = { 0 };

    if (argv[1] == NULL)
        serv_addr.sin_port = 43522;
    else
        serv_addr.sin_port = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;    
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    printf("Using port: %d\n", serv_addr.sin_port);

    serv_sock_d = socket(AF_INET, SOCK_DGRAM, 0);
    if ( serv_sock_d == -1 )
    {
        fprintf(
            stderr,
            "socket() returned -1\n"
            "errno: % 3d\t`%s`\n"
            "Exiting..\n",
            errno, strerror(errno));
        exit(errno);
    }
    printf("Socket created\n");

    result = bind(serv_sock_d, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (result == -1)
    {
        fprintf(
            stderr,
            "bind() returned -1\n"
            "errno: % 3d\t`%s`\n"
            "Exiting..\n",
            errno, strerror(errno));
        exit(errno);
    }
    printf("Bind success\n");
    
    #if 0
    if (result == -1)
    {
        fprintf(
            stderr,
            "listen() returned -1\n"
            "errno: % 3d\t`%s`\n"
            "Exiting..\n",
            errno, strerror(errno));
        exit(errno);
    }
    #endif
    result2 = sizeof(serv_addr);
    for (size_t i = 0; i < sizeof(recv);)
    {
        printf("Wait for data...\n");
        result = recvfrom(
            serv_sock_d,
            &recv_buf[i],
            10,
            0,
            (struct sockaddr*)&serv_addr,
            &result2
        );
        if (result == -1)
            break;
        i += result;
        
        printf("CLIENT: %d `%.*s`\n", result, result, recv_buf);
    }

    close(serv_sock_d);
    printf("Server shutdown..\n");
    return 0;
}
