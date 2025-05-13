#include <stdio.h>

int get_next_permutation(char* permutation, int n) {
    int i = n - 1;
    while (i > 0 && permutation[i-1] >= permutation[i]) {
        i--;
    }
    if (i <= 0) 
        return (0);
    int j = n;
    while (j > i && permutation[j-1] <= permutation[i-1]) {
        j--;
    }
    char temp = permutation[i-1];
    permutation[i-1] = permutation[j-1];
    permutation[j-1] = temp;

    i++;
    j = n;
    while (i < j) {
        temp = permutation[i-1];
        permutation[i-1] = permutation[j-1];
        permutation[j-1] = temp;
        i++;
        j--;
    }

    return (1);
}

void sort_char_arr(char *arr, size_t size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                char tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

size_t ft_strlen(char *str)
{
    size_t len = 0;

    while (str[len])
        len++;
    return (len);
}

int main(int ac, char *av[])
{
    if (ac != 2)
        return (0);

    char *str = av[1];
    size_t len = ft_strlen(str);

    sort_char_arr(str, len);
    do {
        printf("%s\n", str);
    } while (get_next_permutation(str, len));

    return (0);
}