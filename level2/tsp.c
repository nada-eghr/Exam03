#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


 
#include <errno.h>
#include <math.h>
#include <float.h>
//-----------------------------
static bool *visited;
static float length;
static ssize_t size_g;
static float (*cities)[2];
//-----------------------------

float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}
//-----------------------------
void backtrack(int current , int count , float current_len)
{
    if (count == size_g)
    {
        float total = current_len + distance(cities[current] , cities[0]);
        if ( total < length)
            length = total;
        return ;
    }
    for ( int i = 0; i < size_g; i++)
    {
        if(!visited[i] )
        {
            visited[i] = true;
            float new = current_len + distance(cities[current] , cities[i]);
            backtrack(i , count + 1 ,new);
            visited[i] = false;
        }

    }
}
float tsp(float ( *array)[2] , ssize_t size)
{
    length = INFINITY;
    size_g = size;
    cities = array;
    visited = calloc(size , sizeof(bool));
    visited[0] = true;
    backtrack( 0 , 1, 0.0);
    int result = length ;
    free(visited);
    return result;
    }
//----------------------------

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    printf("%.2f\n", tsp(array, size));
    free(array);
}