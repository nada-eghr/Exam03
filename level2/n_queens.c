#include<stdio.h>
#include<stdlib.h>

void hell(int a , int b , int *c)
{
    int safe;
    int d;
    if ( a == b)
    {
        for (int i = 0; i < a ; i++)
            printf("%d%c", c[i] , i < a- 1 ? ' ' : '\n');
        return ;
    }
    for(int r = 0; r < a ; r++)
    {
        safe = 1;
        for ( int i = 0; i < b ; i++)
        {
            d = b - i;
            if ( c[i] == r || c[i] == r + d || c[i] == r - d)
            {
                safe = 0;
                break ;
            }
        }
        if(safe)
        {
            c[b] = r;
            hell( a, b + 1 , c);
        }
    }
}
void hell2(int n)
{
    int b[n];
    hell(n , 0 , b);

}
int main(int ac , char **av)
{
    if ( ac != 2 || atoi(av[1]) <= 0)
        return 1;
    hell2(atoi(av[1]));
}