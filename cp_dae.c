#include "cp_dae.h"

int sock;
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
    while (1)
    {
        if (listen(sock, 0))
            return (perror(""), close(sock), 1);
    }
}