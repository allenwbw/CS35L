//
//  main.c
//  tr2u
//
//  Created by Wang Bowei on 2/20/16.
//  Copyright (c) 2016 Wang Bowei. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of operands.\n");
        exit(1);
    }
    int len1 = strlen(argv[1]);
    int len2 = strlen(argv[2]);
    if (len1 != len2) {
        fprintf(stderr, "Arguments have different length.\n");
        exit(1);
    }
    for (int i = 0; i < len1-1; i++) {
        for (int j = i+1; j<len1; j++) {
            if (argv[1][j] == argv[1][i]) {
                fprintf(stderr, "Duplicate characters in operand 1.\n");
                exit(1);
            }
        }
    }
    char trans[256];
    for (int i= 0; i < 256; i++) {
        trans[i]=i;
    }
    for (int i = 0; i < len1; i++) {
        trans[argv[1][i]]=argv[2][i];
    }
    char a[1];
    while (read(0, a, 1)>0)
        write(1, &trans[(int)*a], 1);
    return 0;
}

