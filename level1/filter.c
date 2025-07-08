#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int ft_strncmp(char *s1 , char *s2 , int n)
{
    int i = 0;
    while ( i < n && s1[i] == s2[i])
        i++;
    if ( i == n)
        return 1;
    else
        return 0;
}
int main(int ac , char **av)
{
    int j = 0;
    char c;
    int bytes = read (0 , &c, 1);
    char *buffer = malloc(1000000);

    while (bytes > 0)
    {
        buffer[j++]= c;
        bytes = read(0 , &c, 1);
    }
    int len = strlen(av[1]);
    int i = 0;
    while ( buffer[i])
    {
        if (ft_strncmp(av[1], &buffer[i] , len))
        {
            for (int j = 0; j < len ; j++)
                printf("*");
            i += len;
        }
        else
        {
            printf("%c", buffer[i]);
            i++;
        }

    }
    return 0;
}