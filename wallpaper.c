#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdbool.h>

void scan()
{
    char line[80];
    printf("input: ");
    scanf("%s", line);
    printf("output: %s\n", line);
}

void checkNumberArguments(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("ERROR: expected 3 command line arguments : [.\\filename, arg1 (path of the wallpaper folder), arg2 (size of pictures), arg3 (delay in minutes)]\n");
        exit(1);
    }
    else
    {
        printf("Command line arguments : [%s, %s, %s]\n", argv[1], argv[2], argv[3]);
    }
}

int transformArgToInt(char* argv) {
    int size = atoi(argv);
    if (size == 0) {
        printf("ERROR: the third argument should be a non empty integer : argv[2] = %s\n", argv);
        exit(1);
    }
    return size;
}

long transformArgToLong(char* argv)
{
    long delay = atoi(argv);
    if (delay == 0)
    {
        printf("ERROR: the fourth argument should be a non empty integer : argv[3] = %s\n", argv);
        exit(1);
    }
    return delay;
}

int restartLoop(int i, int max) {
    if (i == max - 1) {
        i = 0;
       } else {
        i++;
       }
    return i;
}

int main(int argc, char *argv[])
{
    checkNumberArguments(argc, argv);
    // second arg = path
    char* const BASE_URI = argv[1];
    // third arg = number of wallapers
    int const SIZE = transformArgToInt(argv[2]);
    // fourth arg = delay before to change wallpaper
    long const DELAY = transformArgToLong(argv[3])*1000; //*60; // x*(*1000 * 60) = x minutes

    int i = 0;
    char str[strlen(BASE_URI) + 4];
    printf("running...");
    do {
        char index[4];
        // todo: function to create this path
        Sleep(DELAY);             // change wallpaper all x minutes
        strcpy(str, BASE_URI);           // parent path
        snprintf(index, 4, "%d", i + 1); // store 4 bytes from the int 'i' to char 'index' variable
        strcat(str, index);              // filename
        strcat(str, ".jpg");             // extension path
        //printf("index %d : %s\n", i, str); // just log index + path
        SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, &str, SPIF_SENDCHANGE);

       i = restartLoop(i, SIZE);
       //i++;
    } while (i < SIZE);

    return 0;
}