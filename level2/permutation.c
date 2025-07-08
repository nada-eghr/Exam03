
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


int is_dup(char *str, int n)
{
    int i = 0;
    while(i < n)
    {
        if(str[i] == str[n])
            return(1);
        i++;
    }
    return (0);
}

int ft_strlen(char *str)
{
    if(!str)
        return(0);
    int i = 0;
    while(str[i])
        i++;
    return(i);
}

void    permutations(char *str, char *buffer, int i, int size)
{
    if(i == size)
    {
        printf("%s\n", buffer);
        return;
    }
    int j = 0;
    while(j < size)
    {
        if(str[j] != '\0')
        {
            buffer[i] = str[j];
            str[j] = '\0';
            permutations(str, buffer, i + 1, size);
            str[j] = buffer[i];
        }
        j++;
    }

}

char *get_str(char *str, int len)
{
    char *new;

    new = malloc(len + 1);
    int i = 0;
    while(str[i])
    {
        if(is_dup(str, i))
            return(printf("error\n"), free(new), NULL);
        new[i] = str[i];
        i++;
    }
    new[i] = 0;
    return(new);
}

int main(int ac , char **av)
{

    if(ac != 2)
        return (1);
    int len = ft_strlen(av[1]);
    char *arg = get_str(av[1], len);
    if(!arg)
        return (1);
    char *buffer = malloc(len + 1);
    buffer[len] = 0;
    permutations(arg, buffer, 0, len);
    free(buffer);
    free(arg);
    return(0);
}
