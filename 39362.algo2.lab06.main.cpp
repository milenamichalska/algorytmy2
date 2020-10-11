// ALGO2 IN1 20C LAB05
// Milena Michalska
// mm39362@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>// malloc
#include <time.h>

int m = 997;

int* initDataList (int* dataList = nullptr) {
    if (dataList == nullptr) dataList = (int*) malloc(sizeof(int) * m);

    for (int i = 0; i < m; i++) {
        dataList[i] = 0;
    }

    return dataList;
}

int h (int key) {
    return ((key % 1000) + 2^(key % 100) +1) % m;
}

int h2 (int key) {
    return (3*key) % 19 + 1;
}

void addObjectToDataListLinear (int key, int* dataList) {
    // if (dataList = nullptr) dataList = initDataList();
    bool collision = true;
    int H = h(key);

    while (collision) {
        if (dataList[H % m] == 0) collision = false;
        else H++;
    }

    dataList[H % m] = key;
}

int findDataObjectLinear (int key, int* dataList) {
    bool loop = false;
    int H = h(key);
    int Hhelper = H;

    if (dataList[H] == key) return dataList[H];
    H++;

    while (!loop) {
        if (dataList[H % m] == key) return H % m;
        else {
            H++;
            if (H % m == Hhelper) loop = true;
        };
    }

    return -1;

}

void addObjectToDataListDouble (int key, int* dataList) {
    bool collision = true;
    int H = h(key);
    int H2 = h2(key);
    int i = 0;

    while (collision) {
        if (dataList[(H + i*H2) % m] == 0) collision = false;
        else i++;
    }

    dataList[H % m] = key;
}

int findDataObjectDouble (int key, int* dataList) {
    bool loop = false;
    int H = h(key);
    int H2 = h2(key);
    int i = 0;
    int Hhelper = H;

    if (dataList[H] == key) return dataList[H];
    i++;

    while (!loop) {
        if (dataList[(H + i*H2) % m] == key) return H % m;
        else {
            i++;
            if (H + i*H2 == Hhelper) loop = true;
        };
    }
    return -1;
}

void deleteObjectDouble(int key, int* dataList) {
    int toDeleteIndex = findDataObjectDouble(key, dataList); 
    if (toDeleteIndex == -1) return;
    else {
        dataList[toDeleteIndex] = -1;
    }
}

void deleteObjectLinear(int key, int* dataList) {
    int toDeleteIndex = findDataObjectLinear(key, dataList); 
    if (toDeleteIndex == -1) return;
    else {
        dataList[toDeleteIndex] = -1;
    }
}

void addXObjectsToDataListLinear (int X, int* dataList) {
    for (int i = 0; i < X; i++) {
        int randKey = rand() % 40000 + 20000;
        if (findDataObjectLinear(X, dataList) == -1) addObjectToDataListLinear(randKey, dataList);
        else i--;
    }
}

void addXObjectsToDataListDouble (int X, int* dataList) {
    for (int i = 0; i < X; i++) {
        int randKey = rand() % 40000 + 20000;
        if (findDataObjectDouble(X, dataList) == -1) addObjectToDataListDouble(randKey, dataList);
        else i--;
    }
}

void displayDataList(int start, int stop, int* dataList) {
    for (int i = start; i < stop; i++) {
        printf("%d \n", dataList[i]);
    }
}

int main() {
    // initialize random seed
	srand(time(NULL));

    int X, k1, k2, k3, k4;
	FILE* fp = fopen("inlab05.txt", "r");
	if (fp == NULL) return -1;
	fscanf (fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
	fclose(fp);

    clock_t begin, end;
	double time_spent;
	begin = clock();

    //adresowanie liniowe
    int* dataList = initDataList();
    deleteObjectLinear(k1, dataList);
    addObjectToDataListLinear(k1, dataList);
    displayDataList(0, 100, dataList);
    addXObjectsToDataListLinear(X, dataList);
    // printf("po dodaniu:");
    displayDataList(0, 100, dataList);
    addObjectToDataListLinear(k2, dataList);
    addObjectToDataListLinear(k3, dataList);
    addObjectToDataListLinear(k4, dataList);
    displayDataList(0, 100, dataList);
    displayDataList(500, 600, dataList);
    deleteObjectLinear(k3, dataList);
    deleteObjectLinear(k4, dataList);
    displayDataList(0, 100, dataList);
    displayDataList(500, 600, dataList);

    end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %lf", time_spent);

    begin = clock();

    int* dataList2 = initDataList();
    deleteObjectDouble(k1, dataList2);
    addObjectToDataListDouble(k1, dataList2);
    displayDataList(0, 100, dataList2);
    addXObjectsToDataListDouble(X, dataList2);
    // printf("po dodaniu:");
    displayDataList(0, 100, dataList2);
    addObjectToDataListDouble(k2, dataList2);
    addObjectToDataListDouble(k3, dataList2);
    addObjectToDataListDouble(k4, dataList2);
    displayDataList(0, 100, dataList2);
    displayDataList(500, 600, dataList2);
    deleteObjectDouble(k3, dataList2);
    deleteObjectDouble(k4, dataList2);
    displayDataList(0, 100, dataList2);
    displayDataList(500, 600, dataList2);

    end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %lf", time_spent);
}