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

// delete function
treenode* Delete(treenode* root, treenode* node);

// functions for deletion
int isLeaf(treenode* node);
int hasOnlyLeftChild(treenode* node);
int hasOnlyRightChild(treenode* node);
treenode* findParent(treenode* root, treenode* node);
treenode* maxVal(treenode* root);

// need this function to decrement size when deleting
void Decrement(treenode* root, treenode* node);
// treenode* minVal(treenode* root); 
// only going to use maxVal in this context

// inorder parsing function for making the bst into an array
void inorder(treenode* root, customer** cArray, int* index);

void mergeSort(customer** cArray, int l, int r);

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
        for(int x = 0; x <= cmdCount; x++) {

            // put the next line into a string
            char cmd[CMDLEN];
            fgets(cmd, CMDLEN, inFile);

            // first token will always be the type of command
            char* token;
            char* rest = cmd;
            token = strtok_r(rest, " ", &rest);
            
            // add command called
            if (strcmp(token, "add") == 0) {
                // finish tokenizing the command
                char* name = strtok_r(rest, " ", &rest);
                int points = atoi(strtok_r(rest, " ", &rest));

                // search for the name in the tree
                treenode* temp = Search(root, name);
                // if the search comes up empty, time to insert it
                if (temp == NULL)
                    temp = Insert(root, name);

                // if the root is null, meaning the tree is empty, simply root it at the current node being inserted
                if (root == NULL)
                    root = temp;

                // add points
                temp->cPtr->points += points;
                
                // output
                fprintf(outFile, "%s %d\n", temp->cPtr->name, temp->cPtr->points);

            }
            // sub command called
            if (strcmp(token, "sub") == 0) {
                // finish tokenizing the command
                char* name = strtok_r(rest, " ", &rest);
                int points = atoi(strtok_r(rest, " ", &rest));

                // search for the name in the tree
                treenode* temp = Search(root, name);
                // if search was empty, print name not found output
                if (temp == NULL)
                    fprintf(outFile, "%s not found\n", name);
                // otherwise, subtract from points
                else {
                    // if the points being subtracted exceeds the customer's current total points, just set it to zero
                    if (temp->cPtr->points <= points)
                        temp->cPtr->points = 0;

                    // otherwise, just subtract normally
                    else
                        temp->cPtr->points -= points;

                    // output
                    fprintf(outFile, "%s %d\n", temp->cPtr->name, temp->cPtr->points);

                }
            }
            // del command called
            if (strcmp(token, "del") == 0) {
                
                // finish tokenizing the command
                char* name = strtok_r(rest, " \n", &rest);

                treenode* temp = Search(root, name);

                if (temp == NULL)
                    fprintf(outFile, "%s not found\n", name);
                
                else {
                    if (root == temp)
                        root = Delete(root, temp);
                    else
                        Delete(root, temp);
                    
                    fprintf(outFile, "%s deleted\n", name);
                }
            }
            // search command called
            if (strcmp(token, "search") == 0) {

                // finish tokenizing the command
                char* name = strtok_r(rest, " \n", &rest);
                int points = NULL;

                treenode* temp = root;

                int depth_counter = -1; // starts at -1 cuz of a quick fix

                while (temp != NULL) {
                    depth_counter++;

                    int cmp = strcmp(temp->cPtr->name, name);

                    // if sought name comes before the node's name, search to the left
                    if (cmp > 0)
                        temp = temp->left;
                    // if it comes after, search to right
                    else if (cmp < 0)
                        temp = temp->right;
                    // if its equal, we found a match
                    else {
                        points = temp->cPtr->points;
                        fprintf(outFile, "%s %d %d\n", name, points, depth_counter);
                        temp = NULL;
                    }
                }
                // points should only get assigned if the node is found, so this should be sufficient for these cases
                if (points == NULL)
                    fprintf(outFile, "%s not found\n", name);
            }
            // count_smaller command called
            if (strcmp(token, "count_smaller") == 0) {

                // finish tokenizing the command
                char* name = strtok_r(rest, " \n", &rest);

                treenode* temp = root;

                int smaller_count = 0;

                while (temp != NULL) {
                    int cmp = strcmp(temp->cPtr->name, name);

                    // the string is a match
                    if (cmp == 0) {
                        if (temp->left != NULL)
                            smaller_count += temp->left->size;
                        temp = NULL; // no need for further search
                    }
                    // if sought name comes before current node name
                    else if (cmp > 0) {
                        temp = temp->left;
                    }
                    // if sought name is after current node name
                    else if (cmp < 0) {
                        smaller_count++;
                        if (temp->left != NULL)
                            smaller_count += temp->left->size;
                        temp = temp->right;
                    }
                }

                fprintf(outFile, "%d\n", smaller_count);
            }
        }
        // after command loop is done, put bst into array
        int arraySize = root->size;
        customer** cArray = (customer**)malloc(sizeof(customer*)*arraySize);
        int* o = malloc(sizeof(int));
        *o = 0;
        inorder(root, cArray, o);
        mergeSort(cArray, 0, arraySize-1);
        for (int x = 0; x < arraySize; x++) {
            fprintf(outFile, "%s %d\n", cArray[x]->name, cArray[x]->points);
            free(cArray[x]);
        }
        free(cArray);
        free(o);
    }
}

// node creation function
treenode* CreateNode(char* name) {

    customer* c = (customer*)malloc(sizeof(customer));
    strcpy(c->name, name);
    c->points = 0;

    treenode* node = (treenode*)malloc(sizeof(treenode));
    node->cPtr = c;
    node->left = NULL;
    node->right = NULL;
    node->size = 1;

    return node;

}

// bst insertion function
treenode* Insert(treenode* root, char* name) {
    
    // this should only get called if the bst was empty,
    if (root == NULL) {
        root = CreateNode(name);
        return root;
    }

    root->size++; // since the node will definitely be inserted below this current root, might as well increment it to save us a headache

    int cmp = strcmp(root->cPtr->name, name);

    // if the sought name comes before the current node lexographically, search the left node next
    if (cmp > 0) {

        if (root->left == NULL) {
            root->left = CreateNode(name);
            return root->left;
        }
        
        else Insert(root->left, name);

    }

    // if it comes after, search the right node
    else if (cmp < 0) {

        if (root->right == NULL) {
            root->right = CreateNode(name);
            return root->right;
        }
        
        else Insert(root->right, name);
    }
}

// search function, goes thru tree from root 
treenode* Search(treenode* root, char* name) {

    // terminating condition
    if (root == NULL)
        return NULL;

    int cmp = strcmp(root->cPtr->name, name);

    // if the sought name comes before the current node lexographically, search the left node next
    if (cmp < 0)
        Search(root->right, name);

    // if it comes after, search the right node
    else if (cmp > 0)
        Search(root->left, name);

    // if the two are equal, a match has been found
    else if (cmp == 0)
        return root;
}

// deletion function
treenode* Delete(treenode* root, treenode* node) {
    
    treenode* parent = findParent(root, node);
    treenode* replacement;

    // if the target node is a leaf, ez
    if (isLeaf(node)) {
        replacement = NULL;
        Decrement(root, node);
    }

    // if it has one child
    else if (hasOnlyLeftChild(node)) {
        replacement = node->left;
        Decrement(root, replacement);
        replacement->size = node->size;
    }

    else if (hasOnlyRightChild(node)) {
        replacement = node->right;
        Decrement(root, replacement);
        replacement->size = node->size;
    }
    
    // if it has two children
    else {
        replacement = maxVal(node->left);

        Decrement(root, replacement);
        replacement->size = node->size;

        replacement->right = node->right;
        //there are two possibilities. in one, the max value of the left subtree is simply the root of the left subtree. in this case, we can leave its left pointer as is, and only replace the right pointer. otherwise, the replacement will be a right leaf node, in which case, we will need to add the left pointer of the original node as well, and also set it's original parent pointer to null.
        if (replacement != node->left) {
            replacement->left = node->left;
            treenode* repParent = findParent(node, replacement);
            repParent->right = NULL;
        }
        
    }

    if (parent != NULL) {

        if (parent->left == node)
            parent->left = replacement;
        
        else
            parent->right = replacement;

    }

    // now, free this stuff
    free(node->cPtr);
    free(node);
    return replacement;
}

// deletion utility functions
int isLeaf(treenode* node) {
    if (node->left == NULL && node->right == NULL)
        return 1;
    else
        return 0;
}

int hasOnlyLeftChild(treenode* node) {
    if (node->left != NULL && node->right == NULL)
        return 1;
    else
        return 0;
}

int hasOnlyRightChild(treenode* node) {
    if (node->left == NULL && node->right != NULL)
        return 1;
    else
        return 0;
}

treenode* findParent(treenode* root, treenode* node) {
    
    // neither of these cases have parents
    if (root == NULL || root == node)
        return NULL;
    
    // terminating condition for finding the parent of the sought node
    else if (root->left == node || root->right == node)
        return root;
    
    int cmp = strcmp(root->cPtr->name, node->cPtr->name);
    
    // if the sought node comes before the current root lexographically, search the left node next
    if (cmp < 0)
        findParent(root->right, node);

    // if it comes after, search the right node
    else if (cmp > 0)
        findParent(root->left, node);
}

treenode* maxVal(treenode* root) {
    
    // if a right child exists, keep searching from there
    if (root->right != NULL)
        maxVal(root->right);
    
    // otherwise, root is maxval
    else
        return root;
}

void Decrement(treenode* root, treenode* node) {
    
    root->size--;

    if (root == NULL || root == node)
        return;

    int cmp = strcmp(root->cPtr->name, node->cPtr->name);

    // if the sought name comes before the current node lexographically, search the left node next
    if (cmp < 0)
        Decrement(root->right, node);

    // if it comes after, search the right node
    else if (cmp > 0)
        Decrement(root->left, node);

    // if the two are equal, a match has been found
    else if (cmp == 0)
        return;
}

// inorder parsing function for making the bst into an array
void inorder(treenode* root, customer** cArray, int* index) {
    // terminating condition
    if (root != NULL) {
        inorder(root->left, cArray, index); // left subtree
        cArray[*index] = root->cPtr; // add root to array
        (*index)++; // increment int pointer
        inorder(root->right, cArray, index); // right subtree
        free(root);
    }
}

void mergeSort(customer** cArray, int l, int r)
{
	// terminating condition
	if (l >= r) return;
	else {

		int mid = (l+r)/2; // midpoint

		// recursive call;
		mergeSort(cArray, l, mid);
		mergeSort(cArray, mid+1, r);

		// now we need to actually merge things
		// lengths of temp arrays
		int lSize = mid - l + 1;
		int rSize = r - mid;

		// temp arrays
		customer** lArray = (customer**)malloc(lSize*sizeof(customer*));
		customer** rArray = (customer**)malloc(rSize*sizeof(customer*));

		// populate temp arrays
		for (int x = 0; x < lSize; x++)
			lArray[x] = cArray[l + x];
		
		for (int y = 0; y < rSize; y++)
			rArray[y] = cArray[mid+1 + y];

		// put data from temp arrays back into array
		int m = 0, n = 0; // indexes for temp arrays
		for (int p = l; p < r+1; p++) {
			
			// if we've already run out of entries in rArray but lArray still has some left
			if (n >= rSize && m < lSize) {
				cArray[p] = lArray[m];
				m++;
			}
			// vice versa
			else if (m >= lSize && n < rSize) {
				cArray[p] = rArray[n];
				n++;
			}
			// otherwise, compare the two and determine which to put first
			else {

				if (lArray[m]->points > rArray[n]->points) {
					cArray[p] = lArray[m];
					m++;
				}
				else if (lArray[m]->points < rArray[n]->points) {
					cArray[p] = rArray[n];
					n++;
				}
                else {
                    int cmp = strcmp(lArray[m]->name, rArray[n]->name);
                    if (cmp < 0) {
                        cArray[p] = lArray[m];
					    m++;
                    }
                    else if (cmp > 0) {
                        cArray[p] = rArray[n];
					    n++;
                    }
                }
			}
		}

		free(lArray);
		free(rArray);
 	}
}