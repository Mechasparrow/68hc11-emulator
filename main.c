#include <stdio.h>
#include "cpu.h"


int main(void) {
	
	CPU cpu = createCPU();

	printf("Step 0:\n");

	MOV(&cpu, 0x0A, 0x0A);
	MOV(&cpu, 0xB0, 0x0B);
	printCpuData(&cpu);
	printf("\n");

	printf("Step 1:\n");
	LDAA_FROM_MEMORY(&cpu, 0x0A);
	LDAB_FROM_MEMORY(&cpu, 0x0B);
	printCpuData(&cpu);

	printf("\n");
	printf("Step 2:\n");
	printf("ABA\n");

	ABA(&cpu);
	
	printCpuData(&cpu);
	printf("\n");

	destroyCPU(&cpu);

	return 0;
}
