#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RAYSIZE 100

typedef unsigned int uint;           // added by Grant, not sure why I need this but I do..

//forward declarations
typedef struct tnode {
    char strName[RAYSIZE];
    int strQty;
    struct tnode* lChild;
    struct tnode* rChild;
} tnode;

void insert(tnode**, char[RAYSIZE]);
void print(FILE *f, tnode*);
void clearTree( tnode*);
void readin(FILE *f, tnode** root);


int main(int args, char** argv) {
    /*
     * Go to Run > Edit Configs >
     * in the program arguments field past in the full path of the
     * string.txt file with double quotes around it,
     * that should be all you need to do
     */
    char* filePath;
    filePath = argv[1];
    printf("%s", filePath);
    FILE *fptr = fopen(filePath,"r");      // input file
    FILE *outfptr = fopen("output.txt", "a");  // output file

    if (fptr == NULL) {
        perror("Error opening file: ");
        return 1;
    }

    // Pointer for root of our tree
    tnode* root = NULL;
    // Stdin our words into the tree
    readin(fptr, &root);

    // PRINT TREE
    print(outfptr, root);
    //Free dynamic memory
    clearTree(root);
    root = NULL;

    // closing input and output files
    fclose(fptr);
    fclose(outfptr);

    return 0;
} // end main

//--------------------------------
// READIN FUNCTION
// Precondition: Address of root and file to be read from
// Postcondition: EOF has been reached an words have been inserted
// Returns: Nothing.
//--------------------------------
void readin(FILE *f, tnode** root) {
    // Assumption word will not be longer than 256 characters long.
    char word[RAYSIZE];

    // Reads a string. This will stop on the first whitespace character reached or at 100 characters.
    while (fscanf(f, "%99s", word) == 1)
    {
        puts(word);
        insert(root, word);
    }
}

//-------------------------------
// INSERT FUNCTION
// Precondition: Address of root and string to be inserted is passed in
// Postcondition: String is inserted into tree or incremented if it already exists
// Returns: Nothing.
//-----------------------------------
void insert(struct tnode** root, char Str1[RAYSIZE]){
    //checks to see if tree is empty, if so sticks str1 as the root
    if (*root == NULL){
        struct tnode* tempNode = (tnode*) malloc(sizeof(tnode));
        strcpy(tempNode->strName, Str1);
        tempNode->strQty = 1;
        tempNode->lChild = NULL;
        tempNode->rChild = NULL;
        *root = tempNode;
        return;
    }
    //if tree is not empty find where it goes
    tnode* previous = NULL;//tracks previous nodes
    tnode* current = *root;//tracks current nodes

    while(current != NULL) {
        // if string is already in tree increments the quantity of that string and leaves function
        if (strcmp(Str1, current->strName) == 0) {
            current->strQty += 1;
            return;
        }
            // if passed in string is less than current string go left
        else if (strcmp(Str1, current->strName) < 0) {
            previous = current;
            current = current->lChild;
        }
            //if string is larger it goes right
        else {
            previous = current;
            current = current->rChild;
        }
    }
    //when loop breaks new node will attach to previous node
    //creates a new node
    tnode* tempNode = (tnode*) malloc(sizeof(tnode));
    strcpy(tempNode->strName, Str1);
    tempNode->strQty = 1;
    tempNode->lChild = NULL;
    tempNode->rChild = NULL;
    //figures out if new node connects to left or right and sticks it in there
    if (strcmp(Str1, previous->strName) < 0){
        previous->lChild = tempNode;
    }
    else{
        previous->rChild = tempNode;
    }
}//end insert

//---------------------------------------------------------
// PRINT FUNCTION
// Precondition: root is passed in
// Postcondition: Prints out tree in order including qty of each word
// Returns: Nothing
//----------------------------------------------------------------
void print(FILE *f,tnode* root){
    //if there is a left child call print recursively
    if (root->lChild != NULL){
        print(f, root->lChild);
    }
    // print out value since no left children left
    printf("%s : %d\n",root->strName, root->strQty);


    /*
     * Writing counts to file
     */
    char count [RAYSIZE];
    sprintf(count, "%d", root->strQty);
    char* stringForOutFile = malloc(strlen(root->strName) + strlen(count) + 4); // + 4 for /n and null terminators, 1 from each word after count caster to a char*

    strcpy(stringForOutFile, root->strName);
    strcat(stringForOutFile, " : ");
    strcat(stringForOutFile, count);
    strcat(stringForOutFile, "\n");

    fputs(stringForOutFile, f);

    free(stringForOutFile);
    /*
     *
     */



    // if there is a right child call print recursively
    if (root->rChild != NULL){
        print(f, root->rChild);
    }
}// end print

//-------------------------------------------------------
// CLEAR FUNCTION
// Precondition: root is passed in
// Postcondition: All memory allocated by tree is cleared
// Returns: Nothing
//------------------------------------------------------------
void clearTree(tnode* root){
    // calls recursively if there is a left child
    if (root->lChild != NULL){
        clearTree(root->lChild);
    }
    // calls recursively if there is a right child
    if (root->rChild != NULL){
        clearTree(root->rChild);
    }
    // if all children have been freed, then free node
    free(root);
}// end clear