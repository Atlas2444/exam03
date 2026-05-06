#include "get_next_line.h"

char *get_next_line(int fd)
{
    int i = 0;
    static int size = 0;
    static int pos = 0;
    static char buf[BUFFER_SIZE];
    char* line = malloc(100000);
    if(fd < 0 || BUFFER_SIZE <= 0 || !line)
        return NULL;
    while(1)
    {
        if(pos >= size)
        {
            size = read(fd, buf, BUFFER_SIZE);
            pos = 0;
            if(size <= 0)
                break;
        }
        line[i++] = buf[pos++];
        if(line[i - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if(i == 0)
    {
        free(line);
        return NULL;
    }
    return line;
}

int main ()
{
	int fd = open("tester.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
