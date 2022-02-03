#include<stdio.h>

int main() {
	float vel, multa;
	scanf("%f", &vel);

	if(vel > 80) {
		multa = 2*(vel - 80);
		printf("Limite de velocidade excedido! Multado no valor de R$%.2f!\n", multa);
	}
	else {
		printf("Velocidade dentro do limite permitido.\n");
	}

	return 0;
}