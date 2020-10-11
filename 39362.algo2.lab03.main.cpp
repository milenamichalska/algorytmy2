// ALGO2 IN1 20C LAB03
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
            //printf("Wezel o podanym kluczu juz istnieje!");
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
        int randKey = rand() % 10000 + (-10000);
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
   // if (!found) printf("Nie znaleziono wezla o podanym kluczu! \n");
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
  //  if (!found) printf("Nie znaleziono rodzica podanego wezla! \n");
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
            parent->leftChild = (parent->leftChild == toDelete) ? toDelete->rightChild : parent->leftChild;
            parent->rightChild = parent->rightChild == toDelete ? toDelete->rightChild : parent->rightChild;
        }
    }

    //drugi stopień, 2 potomków
    if (toDelete->leftChild != nullptr && toDelete->rightChild != nullptr) {
        //printf("key3 %d", key);
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



int main() {
    // initialize random seed
	srand(time(NULL));

    int X, k1, k2, k3, k4;
	FILE* fp = fopen("inlab03.txt", "r");
	if (fp == NULL) return -1;
	fscanf (fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
	fclose(fp);

    clock_t begin, end;
	double time_spent;
	begin = clock();

    BSTNode* root = initBST();
    deleteBSTNode(k1, root);
    insertBSTNode(k1, root);
    inorder(root);
    insertXBSTNodes(X, root);
    printf("inorder: \n");
    inorder(root);
    printf("preorder: \n");
    preorder(root);
    insertBSTNode(k2, root);
    printf("inorder: \n");
    inorder(root);
    insertBSTNode(k3, root);
    insertBSTNode(k4, root);
    deleteBSTNode(k1, root);
    printf("preorder: \n");
    preorder(root);

    end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %lf", time_spent);
}