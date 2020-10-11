// ALGO2 IN1 20C LAB04
// Milena Michalska
// mm39362@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>// malloc
#include <time.h>  

struct BSTNode
{
	int key;
    BSTNode * rightChild;
    BSTNode * leftChild;
    char znaki[10];
};

BSTNode* createBSTNode (int key) {
    BSTNode* node = (BSTNode*) malloc(sizeof(BSTNode));
    node->key = key;
    node->rightChild = nullptr;
    node->leftChild = nullptr;
    sprintf(node->znaki,"%ld", key);
    return node;
}

BSTNode* initBST(BSTNode* root = nullptr) {
    if (root == nullptr) {
        root = createBSTNode(10);
    }
    return root;
}

int insertBSTNode(int key, BSTNode* root = nullptr) {
    BSTNode* previous = nullptr;
    BSTNode* p = root;
    while (p != nullptr) {
        if (p->key == key) {
            // printf("Wezel o podanym kluczu juz istnieje!");
            return -1;;
        }
        previous = p;
        if (p->key < key) p = p->rightChild;
        else p = p->leftChild;
    }

    BSTNode* newNode = createBSTNode(key);

    if (previous == nullptr) { 
        root = newNode;
        return 0;
    }

    if (previous->key < key) previous->rightChild = newNode;
    else previous->leftChild = newNode;
    return 0;
}

void insertXBSTNodes(int X, BSTNode* root = nullptr) {
    for (int i = 0; i < X; i++) {
        int randKey = rand() % 200 - 100;
        i += insertBSTNode(randKey, root);
    }
}

BSTNode* findBSTNode(int key, BSTNode* root = nullptr) {
    bool found = false;
    BSTNode* p = root;
    while((p != nullptr) && !found) {
        if (p->key == key) found = true;
        else if (p->key < key) p = p->rightChild;
        else p = p->leftChild;
    }
    if (!found) printf("Nie znaleziono wezla o podanym kluczu! \n");
    return p;
}

BSTNode* findParent(BSTNode* child, BSTNode* root = nullptr) {
    bool found = false;
    BSTNode* p = root;
    while((p != nullptr) && !found) {
        if ((p->rightChild = child) ||  (p->leftChild = child)) found = true;
        else if (p->key < child->key) p = p->rightChild;
        else p = p->leftChild;
    }
    if (!found) printf("Nie znaleziono rodzica podanego wezla! \n");
    return p;
}

void deleteBSTNode (int key, BSTNode* root = nullptr) {
    BSTNode* p = root;
    BSTNode* toDelete = findBSTNode(key, p);
    if (toDelete == nullptr) return;

    BSTNode* parent = findParent(toDelete, root);
    //liść
    if (toDelete->leftChild == nullptr && toDelete->rightChild == nullptr) {
        parent->leftChild = parent->leftChild == toDelete ? nullptr : parent->leftChild;
        parent->rightChild = parent->rightChild == toDelete ? nullptr : parent->rightChild;
    }

    //pierwszy stopień, tylko 1 potomek
    if (!(toDelete->leftChild == nullptr) != !(toDelete->rightChild == nullptr)) { //xor
        if (toDelete->leftChild != nullptr) {
            parent->leftChild = parent->leftChild == toDelete ? toDelete->leftChild : parent->leftChild;
            parent->rightChild = parent->rightChild == toDelete ? toDelete->leftChild : parent->rightChild;
        }

        if (toDelete->rightChild != nullptr) {
            parent->leftChild = parent->leftChild == toDelete ? toDelete->rightChild : parent->leftChild;
            parent->rightChild = parent->rightChild == toDelete ? toDelete->rightChild : parent->rightChild;
        }
    }

    //drugi stopień, 2 potomków
    if (toDelete->leftChild != nullptr && toDelete->rightChild != nullptr) {
        printf("key3 %d", key);
        BSTNode* tempNode = toDelete->leftChild;
        while (tempNode->rightChild != nullptr) {
            tempNode = tempNode->rightChild;
        }

        parent->leftChild = parent->leftChild == toDelete ? tempNode : parent->leftChild;
        parent->rightChild = parent->rightChild == toDelete ? tempNode : parent->rightChild;

        if (tempNode->leftChild != nullptr) findParent(tempNode)->rightChild = tempNode->leftChild;
        delete (tempNode);
    }

    delete (toDelete);
}

int static inorderVisitedNodes;
int static preorderVisitedNodes;
int static postorderVisitedNodes;

int inorder (BSTNode* root = nullptr) {

    if (root == nullptr) {
        return 0;
	}

    inorder (root->leftChild);
    printf("%d \n", root->key);
	inorder (root->rightChild);

    return inorderVisitedNodes++;
}

int preorder (BSTNode* root = nullptr) {
    if (root == nullptr) {
        return 0;
	}

    printf("%d \n", root->key);
    preorder (root->leftChild);
	preorder (root->rightChild);
	
    return preorderVisitedNodes++;
}

int postorder (BSTNode* root = nullptr) {
    if (root == nullptr) {
        return 0;
	}

    preorder (root->leftChild);
	preorder (root->rightChild);
    printf("%d \n", root->key);

    return postorderVisitedNodes++;
}

void deleteAllNodes (BSTNode* root = nullptr) {
    if (root == nullptr) {
        return;
	}

    deleteAllNodes(root->leftChild);
	deleteAllNodes (root->rightChild);

    delete(root);
}

void rotateRight(BSTNode* grandparent, BSTNode* parent, BSTNode* node, BSTNode* root) {
    //printf("ROTATE RIGHT \n");

    if (grandparent != nullptr) {
        if (grandparent->rightChild == parent) grandparent->rightChild = node;
        else grandparent->leftChild = node; 
    } else {
        root = node;
    }
    
    BSTNode* tmp = node->rightChild;
    node->rightChild = parent;
    parent->leftChild = tmp;
}

void rotateLeft(BSTNode* grandparent, BSTNode* parent, BSTNode* node, BSTNode* root) {
    printf("ROTATE LEFT \n");

    if (grandparent != nullptr) {
        if (grandparent->rightChild == parent) grandparent->rightChild = node;
        else grandparent->leftChild = node; 
    } else {
        root = node;
    }
    
    BSTNode* tmp = node->leftChild;
    node->leftChild = parent;
    parent->rightChild = tmp;
}

int static nodeCounter = 0;

void countNodesRecurrenceFunction(BSTNode* root) {
    if (root == nullptr) {
        return;
	} else {
        nodeCounter++;
        countNodesRecurrenceFunction(root->rightChild);
        countNodesRecurrenceFunction(root->leftChild);
    }
}

int countNodes(BSTNode* root) {
    nodeCounter = 0;
    countNodesRecurrenceFunction(root);
    return nodeCounter;
}

void makeBackbone(BSTNode* root) {
    printf("MAKE BACKBONE \n");
    BSTNode* grandparent = nullptr;
    BSTNode* tmp = root;
    while (tmp != nullptr) {
        if (tmp->leftChild != nullptr) {
            BSTNode* tmp2 = tmp->leftChild;
            rotateRight(grandparent, tmp, tmp->leftChild, root);
            tmp = tmp2;
        }
        else {
            grandparent = tmp;
            tmp = tmp->rightChild;
        }
    } 
}

int findHeight(BSTNode* root) {
    if (root == nullptr) {
        return -1;
    }

    int leftHeight = findHeight(root->leftChild);
    int rightHeight = findHeight(root->rightChild);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

// void balance(BSTNode* root) {
//     makeBackbone(root);
//     printf("%d pozomow \n", findHeight(root));
//     BSTNode* tmp = root, *grandparent = nullptr;

//     int m = 1;
//     int N = countNodes(root);
//     printf("N: %d", N);
//     while (m <= N) m = 2*m + 1;
//     m = m/2;

//     for (int i = 0; i < (N-m); i++) {
//         BSTNode* tmp2 = tmp->rightChild;
//         if (tmp2 != nullptr) {
//             rotateLeft(grandparent, tmp, tmp->rightChild, root);
//             grandparent = tmp2;
//             tmp = tmp2->rightChild;
//         }
//     }

//     while (m > 1) {
//         m = m/2;
//         grandparent = nullptr;
//         tmp = root;

//         for (int i = 0; i < m; i++) {
//             BSTNode* tmp2 = tmp->rightChild;
//             rotateLeft(grandparent, tmp, tmp->rightChild, root);
//             grandparent = tmp2;
//             tmp = tmp2->rightChild;
//         }
//     }
// }

void makeDataTableRecurrentFunction(BSTNode* root, int* datatable, int counter) {
    if (root == nullptr) {
        return;
	}

    makeDataTableRecurrentFunction (root->leftChild, datatable, counter);
    datatable[counter] = root->key;
    // printf("%d \n", root->key);
	makeDataTableRecurrentFunction (root->rightChild, datatable, counter);
    counter++;
}

BSTNode* balanceRecurrent(int* datatable, int first, int last) {
    int middle = (first+last)/2;
    BSTNode* node = nullptr;
    if (first <= last) {
        node = createBSTNode(datatable[middle]);
        node->leftChild = balanceRecurrent(datatable, first, middle - 1);
        node->leftChild = balanceRecurrent(datatable, middle + 1, last);
    }
    return node;
}

void balance(BSTNode* root) {
    int N = countNodes(root);
    int* datatable = (int *) malloc(sizeof(int) * N); 

    makeDataTableRecurrentFunction(root, datatable, 0);

    root = balanceRecurrent(datatable, 0, N-1);
}

int main() {
    // initialize random seed
	srand(time(NULL));

    int X1, X2;
	FILE* fp = fopen("inlab04.txt", "r");
	if (fp == NULL) return -1;
	fscanf (fp, "%d %d", &X1, &X2);
	fclose(fp);

    clock_t begin, end;
	double time_spent;
	begin = clock();

    BSTNode* root = initBST();
    insertXBSTNodes(X1, root);
    printf("%d elementow", countNodes(root));
    printf("%d pozomow \n", findHeight(root));
    balance(root);
    printf("%d pozomow \n", findHeight(root));
    // deleteAllNodes(root);

    // BSTNode* root2 = initBST();
    // insertXBSTNodes(X2, root2);
    // printf("%d pozomow \n", findHeight(root2));
    // balance(root);
    // printf("%d pozomow \n", findHeight(root2));

    end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %lf", time_spent);
}