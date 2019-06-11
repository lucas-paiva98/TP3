#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char const *argv[]) {
	FILE *filePaths;
	int vertexQuantity = 0;
	int edgeQuantity = 0;

	filePaths = fopen("trilhas1.txt", "r");

	if (filePaths == NULL) {
    printf("Error! Cant't open the file.\n");
  	exit(1);
	}

	fscanf(filePaths, "%d %d", &vertexQuantity, &edgeQuantity);

	citiesMatrix = allocateMatrix(edgeQuantity, 2);

	for (int i = 0; i < edgeQuantity; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(filePaths, "%lf", &citiesAux);
			citiesMatrix[i][j] = citiesAux;
		}
	}

	return 0;
}