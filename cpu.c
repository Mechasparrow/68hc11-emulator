#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

void refreshDPointer(CPU * cpu){
    cpu->d.hh = &(cpu->a);
    cpu->d.ll = &(cpu->b);
}

char * getHex(byte b, char buffer[2]){
    
    buffer[0] = '0';
    buffer[1] = '0';

    char hexalpha[16] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F'
    };

    byte bottombits = 0b00001111 & b;
    byte topbits = 0b00001111 & (b >> 4);
    buffer[1] = hexalpha[bottombits%16];
    buffer[0] = hexalpha[topbits%16];

    return buffer;
}

void printCpuData(CPU * cpu) {
    char buff[2];
    printf("A register: $%s\n", getHex(cpu->a, buff));
    printf("B register: $%s\n", getHex(cpu->b, buff));
    printf("D register: $");
    printf("%s", getHex(*(cpu->d.hh), buff));
    printf("%s\n", getHex(cpu->b, buff));
}

void MOV(CPU * cpu, byte value, byte address){
    cpu->rom[address] = value;
}

void LDAA(CPU * cpu, byte value){
    cpu->a = value;
    refreshDPointer(cpu);
}

void LDAA_FROM_MEMORY(CPU * cpu, byte address){
    byte valPtr = cpu->rom[address];
    LDAA(cpu, valPtr);
}

void LDAB(CPU * cpu, byte value){
    cpu->b = value;
    refreshDPointer(cpu);
}

void LDAB_FROM_MEMORY(CPU * cpu, byte address){
    byte valPtr = cpu->rom[address];
    LDAB(cpu, valPtr);
}

void ABA(CPU * cpu){
    byte sum = cpu->a + cpu->b;
    LDAA(cpu, sum);
}


CPU createCPU() {
    CPU actualCpu = {};
    CPU * cpu = &actualCpu;

    if (cpu != NULL){
        cpu->a = (byte)0;
        cpu->b = (byte)0;
        (cpu->d).hh = &(cpu->a);
        (cpu->d).ll = &(cpu->b);
        
        (cpu->pc).hh = &((cpu->rom)[0]);
        (cpu->pc).ll = &((cpu->rom)[1]);

        (cpu->ix).hh = &((cpu->rom)[0]);
        (cpu->ix).ll = &((cpu->rom)[1]);

        (cpu->iy).hh = &((cpu->rom)[0]);
        (cpu->iy).ll = &((cpu->rom)[1]);
        
        (cpu->sp).hh = &((cpu->rom)[0]);
        (cpu->sp).ll = &((cpu->rom)[1]);

        (cpu->flags).flags = (byte)0;

        int i;
        for (i = 0; i < MEMORY_SIZE; i++){
            (cpu->rom)[i] = (byte)0b00000000;
        }


    }

    return actualCpu;
}

void destroyCPU(CPU * cpu) {
    
}
