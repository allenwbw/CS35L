//
//  main.c
//  sfrob
//
//  Created by Wang Bowei on 2/4/16.
//  Copyright (c) 2016 Wang Bowei. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int cmpcount = 0;
int frobcmp(const char * a, const char * b)
{
    cmpcount++;
    if (*a == ' ' && *b == ' ')
        return 0;
    if (*a == ' ')
        return -1;
    if (*b == ' ')
        return 1;
    if ((*a^42) > (*b^42))
        return 1;
    if ((*a^42)<(*b^42))
        return -1;
    if ((*a^42)==(*b^42))
        return frobcmp(a+1,b+1);
}

int cmphelper(const void * a, const void * b)
{
    const char* first = *(const char**) a;
    const char* second = *(const char**) b;
    return frobcmp(first,second);
}


int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        fprintf(stderr, "Wrong number of arguments.");
        exit(1);
    }
    struct stat fileStats;
    fstat(0, &fileStats);
    int sizeofinput = 2048;
    if (S_ISREG(fileStats.st_mode))
        sizeofinput = fileStats.st_size+1;
    char * input = (char*) malloc(sizeof(char) * sizeofinput);
    if (input == NULL) {
        fprintf(stderr, "Allocating dynamic memory failed.");
        exit(1);
    }
    int index = 0;
    int empty = 1;
    char letter;
    while(read(0, &letter, 1)>0)
    {
        empty = 0;
        if (index == sizeofinput)
        {
            sizeofinput *= 2;
            input = (char*) realloc(input, sizeof(char)*sizeofinput);
        }
        if (input == NULL) {
            fprintf(stderr, "Reallocating dynamic memory failed.");
            exit(1);
        }
        input[index] = letter;
        index++;
    }
    if (empty == 1)
        exit(0);
    int wordcount = 0;
    if (input[index-1] != ' ') {
        input[index] = ' ';
        index++;
    }
    for (int i = 1; i<index; i++)
    {
        if (input[i] == ' ' && input[i-1] != ' ')
            wordcount++;
    }
    if (wordcount == 0)
      exit(0);
    char** list = (char**) malloc(sizeof(char*) * wordcount);
    int* wordlenth = (int*) malloc(sizeof(int) * wordcount);
    if (list == NULL || wordlenth == NULL)
    {
      fprintf(stderr, "Allocating dynamic memorry failed.");
      exit(1);
    }
    int charnum = 0;
    for (int i = 0; i < wordcount; i++)
    {
        if (i == 0) {
            list[i] = &input[charnum];
            i++;
            charnum++;
        }
        while (input[charnum] != ' ')
        {
            charnum++;
            if (charnum == index)
                break;
        }
        charnum++;
        if (charnum < index)
            list[i] = &input[charnum];
    }
    qsort(list, wordcount, sizeof(char*), cmphelper);
    for (int i = 0; i < wordcount; i++) {
        int length = 0;
        int k = 0;
        while (list[i][k] != ' ')
        {
            k++;
            length++;
        }
        length++;
        wordlenth[i] = length;
    }
    for (int i = 0; i < wordcount; i++) {
        for (int j = 0; j < wordlenth[i]; j++) {
            write(1, &list[i][j], 1);
        }
    }
    fprintf(stderr, "Comparisons: %d\n", cmpcount);
    free(input);
    free(list);
    free(wordlenth);
    exit(0);
}
