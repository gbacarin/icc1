#include<stdio.h>

int main() {
	int ba = 0, dum = 0, tss = 0, n, soma = 0;
	scanf("%i", &n);
	if(n % 11 == 0)	//verifica se a entrada n é multipla de 11, 13 ou 19
		ba = 1; //o valor vira 1 para os números que n for multiplo
	if(n % 13 == 0)
		dum = 1;
	if(n % 19 == 0)
		tss = 1;
	soma = ba + dum + tss; //a soma guarda a quantidade de números que n
						   //é multiplo
	if(soma == 0) //caso não seja multiplo de nenhum
		printf("%i", n);
	else if(soma == 1) { //caso seja multiplo de um
		printf("Ba");
		if(ba == 1)
			printf("Ba");
		else if (dum == 1)
			printf("Dum");
		else
			printf("Tss");
	}
	else if(soma == 2) { //caso seja multiplo de dois
		if(ba == 1)
			printf("BaDum");
		if(dum == 1) {
			if(ba == 1)
				printf("Dum");
			else
				printf("DumDum");
		}
		if(tss == 1)
			printf("Tss");
	}
	else { //caso seja multiplo de tres
		printf("BaDumTssTss");
	}
	printf("\n");
	return 0;
}