#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include <sys/fcntl.h>
#include<unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif
char *ft_strdup(char *s)
{
	int i = 0;
	char *cp = malloc(sizeof(char) * (strlen(s) + 1));
	if (!cp)
		return NULL;
	while(s[i])
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	return cp;
}
char *get_next_line(int fd)
{
	int i = 0;
	static char buffer[BUFFER_SIZE];
	char line[70000];
	static int b_read;
	static int b_pos;

	if (fd < 0 || BUFFER_SIZE < 1)
		return NULL;
	while (1)
	{
		if (b_pos >= b_read)
		{
			b_read = read(fd , buffer , BUFFER_SIZE);
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
int main()
{
	int fd = open("file.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);
	close(fd);
}