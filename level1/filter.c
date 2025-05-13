#include<unistd.h>
#include<stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif
int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

char *ft_strdup(char *s)
{
    int i = 0;
    char *cp = malloc(sizeof(char) * (ft_strlen(s) + 1));
    if (!cp)
        return NULL;
    while (s[i])
    {
        cp[i] = s[i];
        i++;
    }
    cp[i] = '\0';
    return cp;
}

void putstar(int len)
{
    while (len--)
        write(1, "*", 1);
}
char *get_next_line(int fd)
{
    int i = 0;
    static char buffer[BUFFER_SIZE];
    static int b_pos;
    static int b_read;
    char line[70000];

    if(fd < 0 || BUFFER_SIZE < 1)
        return NULL;
    while (1)
    {
        if (b_pos >= b_read)
        {
            b_read = read(fd, buffer, BUFFER_SIZE);
            b_pos = 0;
            if (b_read <= 0)
                break;
        }
        line[i++] = buffer[b_pos++];
        if (buffer[b_pos - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
        return NULL;
    return (ft_strdup(line));
}
int check_line(char *arg, char *input)
{
    int i = 0;
    while(arg[i])
    {
        if (arg[i] != input[i])
            return 0;
        i++;
    }
    putstar(i);
    return i;
}
int main(int ac , char **av)
{
    int i;
    if ( ac != 2)
        return 0;
    int j;
    char *input;
    while ((input = get_next_line(0)))
    {
        i = 0;
        while (input[i])
        {
            j = check_line(av[1], &input[i]);
            if (j == 0)
                write(1, &input[i++] , 1);
            i += j;
        }
        free(input);
    }
}