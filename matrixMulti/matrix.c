#include<stdio.h>
#include<stdlib.h>



int main() {
	int lA, cA, lB, cB, seed, resp; // lC = lA, cC = cB
	int A[10][10], B[10][10], C[10][10];

	scanf("%d %d", &lA, &cA);
	scanf("%d %d", &lB, &cB);
	if(lA <= 0 || lB <= 0 || cA <= 0 || cB <= 0 || cA != lB) {
		printf("Valores invalidos para a multiplicacao.\n");
		exit(1);
	}
	scanf("%d", &seed);
	srand(seed);

	for (int i = 0; i < lA; i++){
		for (int j = 0; j < cA; j++){
			A[i][j] = rand()% 50 - 25;
			//printf("%i ", A[i][j]);
		}
		//printf("\n");
	}
	//printf("\n");
	for (int i = 0; i < lB; i++){
		for (int j = 0; j < cB; j++){
			B[i][j] = rand()% 50 - 25;
			//printf("%i ", B[i][j]);
		}
		//printf("\n");
	}

	for(int iLinhas = 0; iLinhas < lA; iLinhas++) {
		for(int jColunas = 0; jColunas < cB; jColunas++) {
			resp = 0;
			for(int i = 0; i < cA; i++) {
				resp = resp + (A[iLinhas][i] * B[i][jColunas]);
			}
			C[iLinhas][jColunas] = resp;
		}
	}

	for(int i = 0; i < lA; i++) {
		printf("Linha %i: ", i);
		for(int j = 0; j < cB; j++) {
			printf("%i ", C[i][j]);
		}
		printf("\n");
	}

	return 0;
}