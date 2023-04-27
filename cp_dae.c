#include "cp_dae.h"

#define MSGSIZE 124
int sock;
int c_sock;
ADRESS server_a;

int init_daemon()
{ 
    bzero(&server_a, sizeof(ADRESS));
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return (1);
    server_a.sin_family = AF_INET;
    server_a.sin_port = 900;
    server_a.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sock,(void *)&server_a, sizeof(ADRESS)) < 0)
        return (close(sock), printf("error\n"), 1);
    printf("bind sucsessfull\n");
    return (0);
}
int main (int ac, char  **av)
{
    if (init_daemon())
        return (perror("\n"), 2);
    char    msg[MSGSIZE];
    bzero(&msg, MSGSIZE);
        if (listen(sock, 1))
            return (perror(""), close(sock), 1);
        c_sock = accept(sock, NULL, NULL);
        if (c_sock > 0)
            return perror(""), 1;
        int size = recv(c_sock, msg, MSGSIZE, 0);
        if (size < 0)
            return (perror("mlsg"), 1);
}