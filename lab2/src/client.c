#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <errno.h>
#include <stdint.h>
#include <string.h>

#include "../../include.h"


int main(int argc, char const *argv[])
{
    errno = 0;
    int sd,result,on=1;
    struct sockaddr_in SOCK = { 0 };
    SOCK = (struct sockaddr_in)
    {
        .sin_family = AF_INET,
        .sin_port = htons(43522),
        .sin_addr.s_addr = INADDR_BROADCAST
    
    };
    char buf[] = F" "I" "O"\0";

    printf(F_len % 2 ? "UDP " : "TCP ");
    printf(I_len % 2 ? "Client\n" : "Server\n");
    printf("Data: \"%s\"\n",buf);
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        fprintf(stderr, "socket() - fail\nerrno: %d\t%s\nExit...\n", errno, strerror(errno));
        return errno;
    }

    setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    printf("Socket created\n");
    
    result = sendto(sd, buf, sizeof(buf), 0, (struct sockaddr*)&SOCK, sizeof(SOCK));
    if (result == -1)
    {
        fprintf(stderr, "send() - fail\nerrno: %d\t%s\nExit...\n", errno, strerror(errno));
        return errno;
    }
    printf("sendto() success\t%d\n",result);
    close(sd);
    return 0;
}
