#include "cp_dae.h"

#define MSGSIZE 124
int sock;
int c_sock;
ADRESS server_a;
int size;

int init_socket()
{ 
    bzero(&server_a, sizeof(ADRESS));
    size  = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return (perror(""), 1);
    server_a.sin_family = AF_INET;
    server_a.sin_port = htons(9001);
    server_a.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sock,(void *)&server_a, sizeof(ADRESS)) < 0)
        return (close(sock), perror(""), 1);
    return (0);
}

char *map_file(char *av)
{
    struct stat dd;
    char    *file;
    int fd = open(av, O_RDONLY);
    if (fd  < 0)
        return (perror(""), NULL);
    if (fstat(fd, &dd) == -1)
        return(NULL);
    size = dd.st_size;
    file = mmap(NULL,size , PROT_READ, MAP_PRIVATE, fd, 0);
    if (!file)
        return (close(fd), perror(""), NULL);
    close(fd);
    return(file);
}
int in_daemon()
{
    char    *mapped;
    if (init_socket())
        return (-1);
    char    msg[MSGSIZE];

    bzero(&msg, MSGSIZE);
   
    while (1)
    {
        if (!listen(sock, 1))
        {
            c_sock = accept(sock, NULL, NULL);
            if (c_sock < 0)
                {
                    close(sock);
                    break ;     
                }    
            size = recv(c_sock, msg, MSGSIZE, 0);
            if (size < 0)
                {
                    close(sock);
                    close(c_sock);
                }
            mapped = map_file(msg);
            if (!mapped)
                {
                    send(c_sock, "ko",  2, 0);
                    close(c_sock);
                    close(sock);
                    break ;
                }
            send(c_sock, "ok", 2, 0);
            bzero(msg, MSGSIZE);
            size = recv(c_sock, msg, MSGSIZE, 0);
             int fd = open(msg, O_WRONLY | O_CREAT,0777);
            if (!fd)
                return (perror(""), 1);
            write(fd, mapped, strlen(mapped));
            send(c_sock, mapped, size, 0);
            munmap(mapped, size);
            close(c_sock);
            close(fd);
        }
    }
}
int main()
{
    if (in_daemon())
        return (0);
}