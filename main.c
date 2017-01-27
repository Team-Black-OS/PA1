#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//forward declarations
struct tnode{
    char strName[100];
    int strQty;
    struct tnode* lChild;
    struct tnode* rChild;
};

void insert(struct tnode**, char[100]);
void print(struct tnode*);
void clear(struct tnode*);

int main() {
    // Pointer for root of our tree
    struct tnode* root = NULL;

    char tmp[50] = "Hello";
    // insert nodes insert(&root, "string")
    insert(&root, "Programming");
    insert(&root, "Test");
    insert(&root, "Quiz");
    insert(&root, "In");
    insert(&root, "C");
    insert(&root, "Is");
    insert(&root, tmp);

    // PRINT TREE
    print(root);


    clear(root);


    return 0;
}

//-------------------------------
// INSERT FUNCTION
// Precondition: Address of root and string to be inserted is passed in
// Postcondition: String is inserted into tree or incremented if it already exists
// Returns: Nothing.
//-----------------------------------
void insert(struct tnode** root, char Str1[100]){
    //checks to see if tree is empty, if so sticks str1 as the root
    if (*root == NULL){
        struct tnode* tempNode = malloc(sizeof(struct tnode));
        strcpy(tempNode->strName, Str1);
        tempNode->strQty = 1;
        tempNode->lChild = NULL;
        tempNode->rChild = NULL;
        *root = tempNode;
        return;
    }
    //if tree is not empty find where it goes
    struct tnode* previous = NULL;//tracks previous nodes
    struct tnode* current = *root;//tracks current nodes

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
        struct tnode* tempNode = malloc(sizeof(struct tnode));
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
void print(struct tnode* root){
    //if there is a left child call print recursively
    if (root->lChild != NULL){
        print(root->lChild);
    }
    // print out value since no left children left
    printf("%s : %d\n",root->strName, root->strQty);
    // if there is a right child call print recursively
    if (root->rChild != NULL){
        print(root->rChild);
    }
}// end print

//-------------------------------------------------------
// CLEAR FUNCTION
// Precondition: root is passed in
// Postcondition: All memory allocated by tree is cleared
// Returns: Nothing
//------------------------------------------------------------
void clear(struct tnode* root){
    // calls recursively if there is a left child
    if (root->lChild != NULL){
        clear(root->lChild);
    }
    // calls recursively if there is a right child
    if (root->rChild != NULL){
        clear(root->rChild);
    }
    // if all children have been freed, then free node
    free(root);
}// end clear