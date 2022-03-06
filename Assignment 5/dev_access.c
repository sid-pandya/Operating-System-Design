#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#define TENMB (1048576)

typedef long long lvalue;
int valid(char *toParse, int *value);
int readmouse();
int random();
int tickets();

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Enter:\n\t0 - open dev/input/mouse0 \n\t1 - open dev/urandom \n\t2 - Todo\n");
        return 1;
    }

    int error = valid(argv[1], &value);
    if (error != 0)
    {
        printf("valid input is: ");
        return 1;
    }

    switch (value)
    {
    case 0:
        error = readmouse();
        break;
    case 1:
        error = random();
        break;
    case 2:
        error = tickets();
        break;

    default:
        printf("Enter value from 0 to 2");
        return 1;
    }

    return error;
}

int readmouse0()
{
    int error;
    char text[1024];
    char mem[1];

    int cursor = open("/dev/input/mouse0", O_RDONLY);
    if (cursor == -1)
    {
        printf("mouse0 can not be opened.\n");
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        return 1;
    }

    while (1)
    {
        error = read(cursor, mem, 1);
        if (error == -1)
        {
            if (strerror_r(errno, text, 1024) == 0)
                printf("%s\n", text);
            return 1;
        }
        if (error == 0)
            continue;
        printf("%d\n", mem[0]);
    }
    error = close(cursor);
    if (error == -1)
    {
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        return 1;
    }
    return 0;
}

int valid(char *toParse, int *value)
{
    char *scanitr = toParse;
    if (*scanitr == '-')
        scanitr++;
    if (*scanitr > '1' && *scanitr < '9')
    {
        scanitr++;
        while (*scanitr != '\0')
        {
            if (*scanitr < '0' || *scanitr > '9')
                return 1;
            scanitr++;
        }
    }
    else if (*scanitr != '0' || *(scanitr + 1) != '\0')
        return 1;

    sscanf(toParse, "%d", value);

    return 0;
}

int random()
{

    int error;
    char text[1024];
    char *mem = malloc(TENMB);
    if (mem == NULL)
    {
        puts("Out of memory!");
        exit(1);
    }
    int br = 0;
    int bw = 0;
    struct timeval start;
    struct timeval stop;
    int rand = open("/dev/urandom", O_RDONLY);
    if (rand == -1)
    {
        printf("Failed to open urandom\n");
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s", text);
        return 1;
    }

    int empty = open("/dev/null", O_WRONLY);
    if (empty == -1)
    {
        printf("Failed to open dev/null\n");
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s", text);
        return 1;
    }

    error = gettimeofday(&start, NULL);
    if (error == -1)
    {
        printf("Timer start failed.\n");
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        return 1;
    }

    while (br < TENMB && bw < TENMB)
    {
        error = read(rand, (mem + br), TENMB - br);
        if (error == -1)
        {
            printf("Read error\n");
            if (strerror_r(errno, text, 1024) == 0)
                printf("%s\n", text);
            return 1;
        }

        br += error;

        if (br - bw == 0)
            continue;
        error = write(empty, (mem + bw), br - bw);
        if (error == -1)
        {
            printf("Write error\n");
            if (strerror_r(errno, text, 1024) == 0)
                printf("%s\n", text);
            return 1;
        }
    }

    error = gettimeofday(&stop, NULL);
    if (error == -1)
    {
        printf("Error\n");
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        return 1;
    }

    lvalue usecStart = 1000000 * (lvalue)(start.tv_sec) + (lvalue)(start.tv_usec);
    lvalue usecStop = 1000000 * (lvalue)(stop.tv_sec) + (lvalue)(stop.tv_usec);
    printf("Time used:\t%lld usecs\n", usecStop - usecStart);

    int rval = 0;

    error = close(rand);
    if (error == -1)
    {
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        rval = 1;
    }

    error = close(empty);
    if (error == -1)
    {
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        rval = 1;
    }

    return rval;
}

int tickets()
{
    int error;
    char text[1024];
    int tkt = open("/dev/ticket0", O_RDONLY);
    if (tkt == -1)
    {
        printf("Failed to open /dev/ticket0\n");
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        return 1;
    }

    int i;
    for (i = 0; i < 10; i++)
    {
        int tktno;
        error = read(tkt, &tktno, 4);
        if (error != 4)
            printf("Read %d failed\n", i);
        else
            printf("Ticket: %d\n", tktno);
        sleep(1);
    }

    error = close(tkt);
    if (error == -1)
    {
        if (strerror_r(errno, text, 1024) == 0)
            printf("%s\n", text);
        return 1;
    }

    return 0;
}
