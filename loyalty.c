// COP3502C // Programming Assignment #4 // Mina Georgoudiou // 03/30/24

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// max cmd length
#define CMDLEN 35
// max name length
#define MAXLEN 19

// customer struct
typedef struct customer {
char name[MAXLEN+1];
int points;
} customer;

// tree node struct
typedef struct treenode {
customer* cPtr;
int size;
struct treenode* left;
struct treenode* right;
} treenode;

// takes two node pointers and compares the name strings
int NodeCompare(treenode* a, treenode* b);

// node creation function
treenode* CreateNode(char* name);

// bst insertion function, returns root
treenode* Insert(treenode* root, treenode* node);

// search function, goes thru tree from root 
treenode* Search(treenode* root, char* name);

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

        // first line of input should be a count of how many commands are being inputted
        int cmdCount;
        fscanf(inFile, " %d", &cmdCount);
        
        // execute command loop this many times
        for(int x = 0; x < cmdCount; x++) {

            // put the next line into a string
            char cmd[CMDLEN];
            fgets(cmd, CMDLEN, inFile);

            // first token will always be the type of command
            char* cmdType = strtok(cmd, " ");
            
            // add command called
            if (strcmp(cmdType, "add") == 0) {
                
            }
            // sub command called
            if (strcmp(cmdType, "sub") == 0) {
                
            }
            // del command called
            if (strcmp(cmdType, "del") == 0) {
                
            }
            // search command called
            if (strcmp(cmdType, "search") == 0) {
                
            }
            // count_smaller command called
            if (strcmp(cmdType, "count_smaller") == 0) {
                
            }
        }
    }
}

// takes two node pointers and compares the name strings
int NodeCompare(treenode* a, treenode* b) {

    char* aName = a->cPtr->name; // hopefully this works right
    char* bName = b->cPtr->name;

    return strcmp(aName, bName);

}

// node creation function
treenode* CreateNode(char* name) {

}

// bst insertion function, returns root
treenode* Insert(treenode* root, treenode* node) { 

}

// search function, goes thru tree from root 
treenode* Search(treenode* root, char* name) {

}