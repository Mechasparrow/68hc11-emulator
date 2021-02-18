
#define MEMORY_SIZE 65536
typedef char byte;
typedef struct _two_byte {
	byte * hh;
	byte * ll;
} twobyte;

typedef struct _two_bytes {
	byte hh;
	byte ll;
} twobytes;

typedef struct _cpu_flags {
	byte flags;
} CPU_FLAGS;

struct _cpu_data {
	twobyte d;
	byte a;
	byte b;
	twobyte ix;
	twobyte iy;
	twobyte sp;
	twobyte pc;
	CPU_FLAGS flags;
	byte rom[MEMORY_SIZE];
}; 

typedef struct _cpu_data CPU;

void printCpuData(CPU * cpu);
CPU createCPU();
void destroyCPU(CPU * cpu);
void MOV(CPU * cpu, byte value, byte address);

void LDAA(CPU * cpu, byte value);
void LDAA_FROM_MEMORY(CPU * cpu, byte address);

void LDAB(CPU * cpu, byte value);
void LDAB_FROM_MEMORY(CPU * cpu, byte address);

void ABA(CPU * cpu);