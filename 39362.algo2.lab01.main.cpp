// ALGO2 IN1 20C LAB01
// Milena Michalska
// mm39362@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>// malloc
#include <time.h>   

struct Struktura
{
	int i;
	char c;
	float f;
};

int uniqueRandom(Struktura** tab, int counter) {
	bool isUnique = false;
	int tempRandom = 0;

	while (!isUnique) {
		tempRandom = rand() % 9000 + (-1000);
		isUnique = true;
		for (int j = 0; j < counter; j++) {
			if (tab[j]->i == tempRandom) {
				isUnique = false;
			}
		} 
	}
	
	return tempRandom;
}

Struktura** losowanie(const int N) {
	//alokacja pamięci na tablicę N wskaźników na struktury
	struct Struktura** tab = (struct Struktura**) malloc(N * sizeof(struct Struktura*));

	for (int i = 0; i < N; i++) {
		//alokacja pamięci na pojedynczą strukturę z przypisaniem adresu do i-tej pozycji tablicy tab[]
		tab[i] = (struct Struktura*) malloc(sizeof(struct Struktura));

		if (tab[i] != NULL)
		{
			int tempInt = uniqueRandom(tab, i);

			tab[i]->i = tempInt;
			tab[i]->c = (char)'B' + rand() % 18;
			tab[i]->f = 1000 + i + 1;

			// printf("tab[%d] = %d\n",i,tempInt);
		}
	}

	return tab;
}

void kasowanie(Struktura** tab, int N) {
	for (int i = 0; i < N; i++) {
		free(tab[i]);
	}
	free(tab);
	tab = nullptr;
}

Struktura** sortowanie(Struktura** tab, int N) {
	int i, j;
	for (i = 0; i < N - 1; i++) {
		for (j = 0; j < N - i - 1; j++) {
			if (tab[j]->i > tab[j + 1]->i) {
				struct Struktura* temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
		}
		// printf("tab[%d] = %d\n",i,tab[i]->i);
	}
	return tab;
}

int zliczanie_znakow(Struktura** tab, int N, char c) {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		if (tab[i]->c == c) counter++;
	}
	return counter;
}

int main()
{
	// initialize random seed
	srand(time(NULL));

	int N;
	char X;
	FILE* fp = fopen("inlab01.txt", "r");
	if (fp == NULL) return -1;
	fscanf (fp, "%d %c", &N, &X);
	fclose(fp);

	clock_t begin, end;
	double time_spent;
	begin = clock();

	/* here, do your time-consuming job */
	Struktura** tab = losowanie(N);
	tab = sortowanie(tab, N);
	printf("first 20 sorted structs: \n");

	for (int h = 0; h < 20; h++) {
		printf("Struktura %d: i = %d, c = %c, f = %f \n", h, tab[h]->i, tab[h]->c, tab[h]->f);
	}

	int counter = zliczanie_znakow(tab,N,X);
	printf("found X %d times \n", counter);
	kasowanie(tab,N);

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %lf", time_spent);
}
