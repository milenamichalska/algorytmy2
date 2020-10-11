// ALGO2 IN1 20C LAB02
// Milena Michalska
// mm39362@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>// malloc
#include <time.h>   

struct SkipListNode
{
	int key;
	char c;
	double d;
    SkipListNode * nextNodes[10]; 
};

void addSkipListNode (SkipListNode* head, int key, int lmax) {
    while (head->nextNodes[0] != nullptr && head->nextNodes[0]->key < key) {
        head = head->nextNodes[0];
    }

    SkipListNode* tempNext = head->nextNodes[0];

    head->nextNodes[0] = (SkipListNode*) malloc(sizeof(SkipListNode));
    head->nextNodes[0]->key = key;
    head->nextNodes[0]->d = rand();

    if (tempNext != nullptr && tempNext->key == key) {
        tempNext->c = 'D';
        head->nextNodes[0]->c = 'D';
    } else {
        head->nextNodes[0]->c = 'T';
    }

    int levels = rand() % 1 + lmax;
    for (int l = 0; l < levels; l++) {
        if (l = 0) {
            head->nextNodes[0]->nextNodes[l] = tempNext;
        } else {
            
        }

    }
} 

void printSkipList (SkipListNode* head) {
    while (head->nextNodes[0] != nullptr) {
        printf("node %d, char %c\n", head->key, head->c);
        head = head->nextNodes[0];
    }
}

int main() {
    srand(time(NULL));
    int lMax = 10;

    // SkipListNode* tail = (SkipListNode*) malloc(sizeof(SkipListNode));
    // tail->i = 1;
    // tail->c = 'a';
    // tail->f = 0;
    // tail->next = nullptr;

    SkipListNode* head = (SkipListNode*) malloc(sizeof(SkipListNode));
    head->key = 0;
    head->c = 'T';
    head->d = 0;
    head->nextNodes[0] = nullptr;

    addSkipListNode(head, 5, lMax);
    addSkipListNode(head, 3, lMax);
    addSkipListNode(head, 4, lMax);
    addSkipListNode(head, 6, lMax);
    addSkipListNode(head, 4, lMax);
    printSkipList(head);
}