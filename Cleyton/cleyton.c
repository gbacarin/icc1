#include<stdio.h>
#include<stdlib.h>

int main() {
	int tape[512], exec = 0, arg1, arg2, arg3; /*as variaveis arg
	vão receber as posições do vetor tape*/
	for(int i = 0; i < 512; i++) {
		scanf("%d", &tape[i]);
	}
	printf("Saida do programa:\n");
	do {
		if(tape[exec] == 0) // halt
			break;
		else if(tape[exec] == 1) {  // add
			arg1 = tape[exec + 1];
			arg2 = tape[exec + 2];
			arg3 = tape[exec + 3];
			tape[arg3] = tape[arg1] + tape[arg2];
			exec = exec + 4;
		}
		else if(tape[exec] == 2) { //(mul)tiply
			arg1 = tape[exec + 1];
			arg2 = tape[exec + 2];
			arg3 = tape[exec + 3];
			tape[arg3] = tape[arg1] * tape[arg2];
			exec = exec + 4;
		}
		else if(tape[exec] == 3) { //Compare Less Than
			arg1 = tape[exec + 1];
			arg2 = tape[exec + 2];
			arg3 = tape[exec + 3];
			if(tape[arg1] < tape[arg2])
				tape[arg3] = 1;
			else
				tape[arg3] = 0;
			exec = exec + 4;
		}
		else if(tape[exec] == 4) { //Compare EQuals
			arg1 = tape[exec + 1];
			arg2 = tape[exec + 2];
			arg3 = tape[exec + 3];
			if(tape[arg1] == tape[arg2])
				tape[arg3] = 1;
			else
				tape[arg3] = 0;
			exec = exec + 4;
		}
		else if(tape[exec] == 5) { //JuMP
			arg1 = tape[exec + 1];
			exec = tape[arg1];
		}
		else if(tape[exec] == 6) { //Jump if EQual
			arg1 = tape[exec + 1];
			arg2 = tape[exec + 2];
			if(tape[arg1] != 0)
				exec = tape[arg2];
			else
				exec = exec + 3;
		}
		else if(tape[exec] == 7) { //CoPY
			arg1 = tape[exec + 1];
			arg2 = tape[exec + 2];
			tape[arg2] = tape[arg1];
			exec = exec + 3;
		}
		else if(tape[exec] == 8) { //PUT
			arg1 = tape[exec + 1];
			printf("%c", tape[arg1]);
			exec = exec + 2;
		}
		else if(tape[exec] == 9){ // PuT Num
			arg1 = tape[exec + 1];
			printf("%d", tape[arg1]);
			exec = exec + 2;
		}
		else { break; }
	} while(1);

	printf("\nEstado final da fita:\n");
	for(int i = 0; i < 512; i++) {
		printf("%d\n", tape[i]);
	}

	return 0;
}