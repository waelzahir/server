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
    server.sin_addr.s_addr = inet_addr("127.0.0.1");;
    if (connect(sock, (struct sockaddr *)&server, sizeof(ADRESS)) < 0)
        return (close(sock), 1);
    printf("connect succes\n");
    return (0);
}
char        *get_top_file(char  *f)
{
    int i = 0;
    while (f[i])
    {
        if (f[i] == '/')
            return (f);
        i++;
    }
    char    *path = getenv("PWD");
    char    *ret = calloc(strlen(f) + strlen(path)+2, 1);
    if (!ret)
        return (NULL);
    strncat(ret, path, strlen(path));
    strncat(ret, "//", 1);

    strncat(ret, f, strlen(f));
    return (ret);
}
int main(int ac, char   **av)
{
    if (ac != 3)
        return (0);
    if (init_sock())
        return (perror(""), 1);
    char    *src = get_top_file(av[1]);
    char    *dst = get_top_file(av[2]);
    if (!src || !dst)
        return (0);

    if (send(sock, src, strlen(src), 0) < 0)
        return (perror(""), 1);
    recv(sock, buff, 120, 0);
    if (!strncmp(buff, "ok", 2))
        send(sock, dst, strlen(dst), 0);
    else
        exit(-1);
    
    close(sock);
    exit(1);
}