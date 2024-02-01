	// Name and Surname: Muhammet Bugra Guler --- Number: 201180003
//C program to print binary tree reverse level order traversal

#include <stdio.h>
#include <stdlib.h>

//A binary tree node has data, pointer to left and right child
struct treeNode {
    int data;
    struct treeNode* leftptr;
    struct treeNode* rightptr;
};

//Insert new node to the binary tree
struct treeNode* newNode(int data) {
    struct treeNode* treeNode = (struct treeNode*) malloc(sizeof(struct treeNode));
    treeNode->data = data;
    treeNode->leftptr = NULL;
    treeNode->rightptr = NULL;
    return(treeNode);
}

int treeNodeLevel(struct treeNode *root, int i) { // This function calculates binaryTree level.
	if (root != NULL) {
		treeNodeLevel(root->leftptr, i++);
		treeNodeLevel(root->rightptr, i++);
	}
	else if(root == NULL) {
		return i; // Returns tree level.
    }
}

// Define recursive level order function help with this site: https://www.geeksforgeeks.org/reverse-level-order-traversal/
void recursiveLevelOrder(struct treeNode* root,int level) { // This function allows the tree to be written recursively.
	if (level == 0)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1)
    {
        recursiveLevelOrder(root->leftptr, level - 1);
        recursiveLevelOrder(root->rightptr, level - 1);
    }
}

//I wrote this code, but if the level number is greater than 5, the code does not work, so I took help from the internet and wrote a different code.
void reverseLevelOrderTryMyself(struct treeNode *root) {
	struct treeNode *tempRoot, *tempUp, *tempLow; // Create temp nodes.
	int level = treeNodeLevel(root, 0); // Calculate tree level
	int tempLevel = level - 3;
	for(int i = 0; i < (level - 2); i++) { // Prints the left side of the loop first and then switches to the right side.
		tempRoot = root;
		for (int j = 0; j < tempLevel; j++) {
			tempRoot = tempRoot->leftptr;
		}
		tempUp = tempRoot;
		tempLow = tempUp->leftptr;
		printf("%d ", tempLow->leftptr->data);
		printf("%d ", tempLow->rightptr->data);
		tempLow=tempUp->rightptr;
		printf("%d ", tempLow->leftptr->data);
		printf("%d ", tempLow->rightptr->data);
		if (tempLevel > 0) {
			tempRoot = root;
			for (int j = 0; j < (tempLevel - 1); j++) {
			    tempRoot = tempRoot->leftptr;
		    }
		    tempUp = tempRoot;
		    tempRoot = tempUp->rightptr;
		    tempLow = tempRoot->leftptr;
		    printf("%d ", tempLow->leftptr->data);
		    printf("%d ", tempLow->rightptr->data);
		    tempLow = tempRoot->rightptr;
		    printf("%d ", tempLow->leftptr->data);
		    printf("%d ", tempLow->rightptr->data);
		}
		tempLevel--;
	}
	printf("%d ", root->leftptr->data); // Printing root and sub-branch.
	printf("%d ", root->rightptr->data);
	printf("%d ", root->data);
}

//Function to print reverse level order traversal a binary tree
void reverseLevelOrder(struct treeNode *root) {
	struct treeNode *temp = root;
    int level = treeNodeLevel(root, 0); // Call the calculate level function.
    if(level < 5 && level > 1) 
        reverseLevelOrderTryMyself(root); // If it is less than level 5, it sends it to the code I wrote.
    else {
        for (int i = level; i > 0; i--) { // Else, it sends it to the other
    	    recursiveLevelOrder(root, i);
	    }
	}
}

int main() { // Main function
    struct treeNode *root = newNode(9);
    root->leftptr = newNode(12);
    root->rightptr = newNode(21);
    root->leftptr->leftptr = newNode(15);
    root->leftptr->rightptr = newNode(8);
    root->rightptr->leftptr = newNode(7);
    root->rightptr->rightptr = newNode(11);
    printf("Level Order traversal of binary tree is \n");
    reverseLevelOrder(root);
    return 0;
}
