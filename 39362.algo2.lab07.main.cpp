// ALGO2 IN1 20C LAB07
// Milena Michalska
// mm39362@zut.edu.pl

#include <stdio.h>
#include <stdlib.h> // malloc
#include <time.h>
#include <cmath> // floor

int m = 1000;

struct binaryHeap {
    int len;
    int* dataArray;
};

binaryHeap* initHeap (binaryHeap* heap = nullptr) {
    if (heap == nullptr) {
        binaryHeap* newHeap = new binaryHeap;
        newHeap->len = 0;
        newHeap->dataArray = (int*) malloc(sizeof(int) * m);
        heap = newHeap;
    }

    for (int i = 0; i < m; i++) {
        heap->dataArray[i] = 0;
    }

    return heap;
}

void displayHeap (binaryHeap* heap) {
    for (int i = 0; i < heap->len; i++) {
        printf("index: %d, val: %d \n", i, heap->dataArray[i]);
    }
}

void displayArray (int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("index: %d, val: %d \n", i, arr[i]);
    }
}

void addToHeap (binaryHeap* heap, int key) {
    int index = heap->len;

    heap->dataArray[index] = key;
    heap->len++;

    while (index > 0) {
        if (heap->dataArray[index/2] < heap->dataArray[index]) {
            int tempKey = heap->dataArray[index/2];
            heap->dataArray[index/2] = heap->dataArray[index];
            heap->dataArray[index] = tempKey;
            index = index/2;
        } else return;
    }
}

void deleteRoot (binaryHeap* heap = nullptr) {
    if (heap == nullptr) return;

    int index = 0;
    heap->len--;
    heap->dataArray[index] = heap->dataArray[heap->len];
    heap->dataArray[heap->len] = 0;

    while (index < heap->len - 1) {
        if (heap->dataArray[2*index] > heap->dataArray[index]) {
            if (heap->dataArray[2*index] > heap->dataArray[2*index + 1]) {
                int tempKey = heap->dataArray[index*2];
                heap->dataArray[index*2] = heap->dataArray[index];
                heap->dataArray[index] = tempKey;
                index = index*2;
                continue;
            }
        }

        int tempKey = heap->dataArray[index*2 + 1];
        heap->dataArray[index*2 + 1] = heap->dataArray[index];
        heap->dataArray[index] = tempKey;
        index = index*2 + 1;
    };
}

void deleteAllFromHeap (binaryHeap* heap) {
    while (heap->len > 0) {
        deleteRoot(heap);
    }
}

binaryHeap* heapSort (int* dataArray, int len) {
    binaryHeap* heap = initHeap();
    for (int i = 0; i < len; i++) {
        addToHeap(heap, dataArray[i]);
    }
    return heap;
}

void countingSort (int* dataArray, int len) {
    int max = dataArray[0];
    
    for (int i = 0; i < len; i++) {
        if (dataArray[i] > max ) max = dataArray[i];
    }

    int k = max;
    int *countingArray = (int*) malloc(sizeof(int) * (k + 1));

    for (int i = 0; i < (k+1); i++) {
        countingArray[i] = 0;
    }

    //zliczanie
    for (int i = 0; i< len; i++) {
        countingArray[dataArray[i]]++;
    }

    for (int i = 1; i < (k+1); i++) {
        countingArray[i] = countingArray[i] + countingArray[i-1];
    }

    int* sortedArray = (int*) malloc(sizeof(int) * len);

    //wypelnianie tablicy
    for (int i = len - 1; i >= 0; i--) {
        countingArray[dataArray[i]]--;
        sortedArray[countingArray[dataArray[i]]] = dataArray[i];
    }

    dataArray = sortedArray;
    delete(countingArray);
    delete(sortedArray);

    //displayArray(dataArray, len);
    
}

void bucketSort (int* dataArray, int len) {

    int bucketN = 5;
    int **buckets = new int*[bucketN];

    int max = dataArray[0];
    int min = dataArray[0];
    
    for (int i = 0; i < len; i++) {
        if (dataArray[i] > max ) max = dataArray[i];
        if (dataArray[i] < min ) min = dataArray[i];
    }
    
    double roznica_przedziau = max - min;
    double roznica_podprzedzialu = ceil(roznica_przedziau / (double)bucketN);
    int rozmiar_przedzialu = len;
    int rozmiar_podprzedzialu = len; //len / bucketN;

    // int tempBucket0Index = 0;
    // int tempBucket1Index = 0;
    // int tempBucket2Index = 0;
    // int tempBucket3Index = 0;
    // int tempBucket4Index = 0;

    int buckets_index[] = {0,0,0,0,0};


    for (int i = 0; i < bucketN; i++) {
        buckets[i] = new int[rozmiar_podprzedzialu];
    }
    printf("roznica_podprzedzialu = %u \n", (int)roznica_podprzedzialu);
    printf("roznica_przedziau = %u \n", (int)roznica_przedziau);
    printf("min = %u \n", min);
    printf("max = %u \n", max);
    for(int i = 0; i<len; i++) {
        if (dataArray[i] >= min && dataArray[i] < min + (int)roznica_podprzedzialu) {
            buckets[0][buckets_index[0]] = dataArray[i];
            buckets_index[0]++;
        }

        if (dataArray[i] >= min + (int)roznica_podprzedzialu && dataArray[i] < min + 2 * (int)roznica_podprzedzialu) {
            buckets[1][buckets_index[1]] = dataArray[i];
            buckets_index[1]++;
        }

        if (dataArray[i] >= min + 2 * (int)roznica_podprzedzialu && dataArray[i] < min + 3 * (int)roznica_podprzedzialu) {
            buckets[2][buckets_index[2]] = dataArray[i];
            buckets_index[2]++;
        }

        if (dataArray[i] >= min + 3 * (int)roznica_podprzedzialu && dataArray[i] < min + 4 * (int)roznica_podprzedzialu) {
            buckets[3][buckets_index[3]] = dataArray[i];
            buckets_index[3]++;
        }

        if (dataArray[i] >= min + 4 * (int)roznica_podprzedzialu && dataArray[i] < min + 5 * (int)roznica_podprzedzialu) {
            buckets[4][buckets_index[4]] = dataArray[i];
            buckets_index[4]++;
        }
    }
    int* bigArray = (int*) malloc(sizeof(int) * len);

    int already_written_size = 0;

    for (int i = 0; i < bucketN; i++) {
        countingSort(buckets[i], buckets_index[i]);


        for (int j = 0; j < buckets_index[i]; j++) {
            // printf("written size: %d", already_written_size +j);
            // printf(" buckets: %d \n", buckets[i][j]);
            bigArray[already_written_size + j] = buckets[i][j];
        }
        already_written_size+=buckets_index[i];
    }
    //displayArray(bigArray, len);
    dataArray = bigArray;

}

int main() {
    binaryHeap* heap = initHeap();
    int tablica[] = {9, 56, 38, 22, 8, 12, 2, 7, 6, 4};
    countingSort(tablica, 10);
    bucketSort(tablica, 10);
}