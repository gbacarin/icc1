/* receba como entrada uma temperatura em graus Fahrenheit e imprima
na tela seu valor equivalente em graus Celsius */

#include<stdio.h>

int main() {
	double celsius, far;
	scanf("%lf", &far);
	celsius = ((far - 32.0) * (5))/9;
	printf("%.2lf\n", celsius);
	
	return 0;
}