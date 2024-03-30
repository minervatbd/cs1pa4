// COP3502C // Programming Assignment #4 // Mina Georgoudiou // 03/30/24

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("invalid input/output args");
        return -1;
    }
    else {

        // open input file
        FILE* inFile = fopen(argv[1],"r");
        // create or overwrite output file
        FILE* outFile = fopen(argv[2],"w");

        // make sure the files exist
        if (inFile == NULL || outFile == NULL) {
            printf("invalid input/output arg");
            return -1;
        }

        
    }
}