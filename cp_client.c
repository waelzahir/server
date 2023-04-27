#include "cp_client.h"
int sock;
char    buff[120];
int init_sock()
{
    ADRESS server;
    bzero(&server, sizeof(ADRESS));
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return (-1);
    printf("socket created\n");
    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = INADDR_ANY;
    if (connect(sock, (struct sockaddr *)&server, sizeof(ADRESS)) < 0)
        return (close(sock), 1);
    printf("connect succes\n");
    return (0);
}
int main(int ac, char   **av)
{
    if (ac != 3)
        return (0);
    if (init_sock())
        return (perror(""), 1);
    if (send(sock, av[1], strlen(av[1]), 0) < 0)
        perror ("send");
    int fd = open(av[2], O_WRONLY | O_CREAT);
    if (!fd)
        return (perror(""), 1);
    bzero(buff, 120);
    while (recv(sock, buff, 120, 0))
    {
        write(fd, buff, strlen(buff));
        bzero(buff, 120);
    }
    close(fd);
    close(sock);
}