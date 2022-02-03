#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void entradaInvalida() {
	printf("Falha no processamento dos dados.\n");
	exit(1);
}
float calcularDistContorno(int xIni, int yIni, int xFim, int yFim) {
	float dist = fabs((xFim - xIni)) + fabs((yFim - yIni));
	return dist;
}

float calcularDistDireta(int xIni, int yIni, int xFim, int yFim) {
	float dist;
	dist = (pow(xFim - xIni, 2)) + (pow(yFim - yIni, 2));
	dist = sqrt(dist);
	return dist;
}

float calcularDiferenca(int xIni, int yIni, int xFim, int yFim, int tipo) {
	float diferenca, distHerr, distEucl;
	switch(tipo) {
		case 1:
			distHerr = calcularDistContorno(xIni, yIni, xFim, yFim);
			distEucl = calcularDistDireta(xIni, yIni, xFim, yFim);
			diferenca = fabs(distHerr - distEucl);
		break;
		default : diferenca = 0;
	}
	return diferenca;
}

int main() {
	int N, res = 0, bal = 0, par = 0;
	float diffDist = 0.0;
	scanf("%d", &N);
	if(N <= 0) {
		entradaInvalida();
	}
	int terrenos[N][3];

	for(int i = 0; i < N; i++) {
		scanf("%d %d %d", &terrenos[i][0], &terrenos[i][1], &terrenos[i][2]);
		if(terrenos[i][2] != -1 && terrenos[i][2] != 0 && terrenos[i][2] != 1)
			entradaInvalida();
	}

	for(int i = 0; i < N; i++) {
		if(i != (N - 1)) {
			diffDist = diffDist + calcularDiferenca(terrenos[i][0],
													terrenos[i][1],
													terrenos[i + 1][0],
													terrenos[i + 1][1],
													terrenos[i][2]);
		}
		else {
			diffDist = diffDist + calcularDiferenca(terrenos[i][0],
													terrenos[i][1],
													terrenos[0][0],
													terrenos[0][1],
													terrenos[i][2]);
		}
		switch(terrenos[i][2]) {
			case -1: bal++; break;
			case 0: res++; break;
			case 1: par++; break;
		}
	}

	printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\nA diferenca total de distancia percorrida foi de %.2f metros.\n", bal, res, par, diffDist);

	return 0;
}