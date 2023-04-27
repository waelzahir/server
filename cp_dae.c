#include "cp_dae.h"

#define MSGSIZE 124
int sock;
int c_sock;
ADRESS server_a;
int size;

int init_daemon()
{ 
    bzero(&server_a, sizeof(ADRESS));
    size  = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return (1);
    server_a.sin_family = AF_INET;
    server_a.sin_port = htons(9001);
    server_a.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock,(void *)&server_a, sizeof(ADRESS)) < 0)
        return (close(sock), printf("error\n"), 1);
    printf("bind sucsessfull\n");
    return (0);
}
char *map_file(char *av)
{
    struct stat dd;
    char    *file;
    int fd = open(av, O_RDONLY);
    if (fd  < 0)
        return (NULL);
    if (fstat(fd, &dd) == -1)
        return(NULL);
    size = dd.st_size;
    file = mmap(NULL,size , PROT_READ, MAP_PRIVATE, fd, 0);
    printf("size%d\n", size);
    close(fd);
    return(file);
}
int main (int ac, char  **av)
{
    char    * mapped;
    if (init_daemon())
        return (perror("\n"), 2);
    char    msg[MSGSIZE];
    bzero(&msg, MSGSIZE);
        if (listen(sock, 1))
            return (perror(""), close(sock), 1);
        c_sock = accept(sock, NULL, NULL);
        if (c_sock < 0)
            return perror(""), 1;
        int size = recv(c_sock, msg, MSGSIZE, 0);
        if (size < 0)
            return (perror("mlsg"), 1);
        mapped = map_file(msg);
        if (!mapped)
            return (perror(""), 1);
        send(c_sock, mapped, size, 0);
        munmap(mapped, size);
        printf("file sent\n");
}