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

// node creation function
treenode* CreateNode(char* name);

// bst insertion function, returns root
treenode* Insert(treenode* root, char* name);

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

        // null root node pointer to start off the tree
        treenode* root = NULL;

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

// node creation function
treenode* CreateNode(char* name) {

    customer* c = (customer*)malloc(sizeof(customer));
    strcpy(c->name, name);

    treenode* node = (treenode*)malloc(sizeof(treenode));
    node->cPtr = c;
    node->left = NULL;
    node->right = NULL;
    node->size = 1;

    return node;

}

// bst insertion function
treenode* Insert(treenode* root, char* name) {
    
    // terminating condition that shouldnt ever actually be called since it will eventually find a place for the node but just in case
    if (root == NULL) return NULL;

    root->size += 1;

    int cmp = strcmp(root->cPtr->name, name);

    // if the sought name comes after the current node lexographically, search the left node next
    if (cmp < 0) {

        if (root->left == NULL) {
            root->left = CreateNode(name);
            return root->left;
        }
        
        else insert(root->left, name);

    }

    // if it comes before, search the right node
    else if (cmp > 0) {

        if (root->right == NULL) {
            root->right = CreateNode(name);
            return root->right;
        }
        
        else insert(root->right, name);
    }
}

// search function, goes thru tree from root 
treenode* Search(treenode* root, char* name) {

    // terminating condition
    if (root == NULL) return NULL;

    int cmp = strcmp(root->cPtr->name, name);

    // if the sought name comes after the current node lexographically, search the left node next
    if (cmp < 0) Search(root->left, name);

    // if it comes before, search the right node
    else if (cmp > 0) Search(root->right, name);

    // if the two are equal, a match has been found
    else return root;
}