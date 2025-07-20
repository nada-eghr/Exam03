#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void    swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void    print_str(char *str, int len)
{
    write(1, str, len);
    write(1, "\n", 1);
}

void    sort_string(char *str)
{
    int i = 0;
    int j;
    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] > str[j])
                swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
}

void    permute(char *str, int start, int len)
{
    if (start == len)
        return (print_str(str, len));
    int i = start;
    while (i < len)
    {
        sort_string(&str[start]);
        swap(&str[start], &str[i]);
        permute(str, start + 1, len);
        swap(&str[start], &str[i]);
        i++;
    }
}

int    main(int ac, char **av)
{
    if (ac == 2)
    {
        char *str = strdup(av[1]);
        sort_string(str);
        permute(str, 0, strlen(av[1]));
        free(str);
    }
    return (0);
}