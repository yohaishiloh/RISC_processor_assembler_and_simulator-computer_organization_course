#ifndef simulatorFunctions_H
#define simulatorFunctions_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define LINESIZE 500
#define MAXLINES 4096
#define OPCODESIZE 3
#define RDSIZE 2
#define RSSIZE 2
#define RTSIZE 2
#define RMSIZE 2
#define IMMSIZE 4
#define REGNUM 16
#define IOREGNUM 23
#define DISKINMAXLINES 16384
#define MONITORSIZE 65536
#define IONAMESIZE 20

// A struction of the format of each instruction 
typedef struct {
	long opcodeAsInt;
	long rdAsInt;
	long rsAsInt;
	long rtAsInt;
	long rmAsInt;
	long imm1AsInt;
	long imm2AsInt;		
}instruction;

typedef struct interrupt {
	long value;
	struct interrupt* next;
} interrupt;


// General use functions:
void dynamic_mem_free(interrupt* head);


// Input-reading and initializing functions:
long imemin_read(FILE* imemin, instruction instructions[]);
void dmemin_read(FILE* dmemin, long dmem[MAXLINES]);
interrupt* add_irq(interrupt* head, long value);
interrupt* irq2in_read(FILE* irq2in, interrupt* irq2head);
void diskin_read(FILE* diskin, char diskmem[][9]);
void structArrayCreator(long pc, char line[], instruction instruction[MAXLINES]); // a func thats creat a struct array 


void checkAndExecute(long dmem[MAXLINES], long ioRegArray[IOREGNUM], long regArray[REGNUM],long *pc,
	instruction instructionArray[MAXLINES], long *isISR);


// Code operations functions:
void add(long regArray[REGNUM], instruction instruction);
void sub(long regArray[REGNUM], instruction instruction);
void mac(long regArray[REGNUM], instruction instruction);
void and (long regArray[REGNUM], instruction instruction);
void or (long regArray[REGNUM], instruction instruction);
void xor (long regArray[REGNUM], instruction instruction);
void sll(long regArray[REGNUM], instruction instruction);
void sra(long regArray[REGNUM], instruction instruction);
void srl(long regArray[REGNUM], instruction instruction);
void beq(long* pc, long regArray[REGNUM], instruction instruction);
void bne(long* pc, long regArray[REGNUM], instruction instruction);
void blt(long* pc, long regArray[REGNUM], instruction instruction);
void bgt(long* pc, long regArray[REGNUM], instruction instruction);
void ble(long* pc, long regArray[REGNUM], instruction instruction);
void bge(long* pc, long regArray[REGNUM], instruction instruction);
void jal(long* pc, long regArray[REGNUM], instruction instruction);
void lw(long dmem[MAXLINES], long regArray[REGNUM], instruction instruction);
void sw(long dmem[MAXLINES+1], long regArray[REGNUM], instruction instruction);
void reti(long* pc, long ioReg7, long* isISR);
void in(FILE* hwregtraceFile, long* pc, long ioRegArray[IOREGNUM], long regArray[REGNUM], instruction instruction);
void out(FILE* hwregtraceFile, long* pc, long ioRegArray[IOREGNUM], long regArray[REGNUM], instruction instruction);


void interuptionsHandling(long ioRegArray[IOREGNUM], long* pc, long* isISR);
long interupt2(long ioRegArray[IOREGNUM], interrupt* irq2head, long next_irq);
void timer(long ioRegArray[IOREGNUM]);
long irq2Update(interrupt* irq2head, long last_irq);
void diskDrive(long* diskClock, char diskmem[DISKINMAXLINES+1][9], long ioRegArray[IOREGNUM], long dmem[MAXLINES]);
void monitor(long ioRegArray[IOREGNUM], long monitorPixels[MONITORSIZE + 1]);

// General-purpose output printing functions:
void sign_extension(long reg, char dest[], int dest_max_len);
void imm_sign_extension(long immediate, char dest[]);
void full_inst_restore(instruction inst, char dest[], char opcode[], char imm1[], char imm2[]);

// Output files printing functions:
void trace_write(FILE* trace, instruction instruction, long pc_int, long inst_int, long regArray[REGNUM]);
void dmemout_write(FILE* dmemout, long dmem[]);
void regout_write(FILE* regout, long regArray[]);
void leds_write(FILE* leds, long ioRegArray[]);
void display7_write(FILE* leds, long ioRegArray[]);
void hwregtrace(FILE* hwregtraceFile,long ioRegArray[IOREGNUM], instruction instruction, long regArray[REGNUM]);
void diskout_write(FILE* diskout, char diskmem[][9]);
void monitor_write(FILE* monitor_txt, FILE* monitor_yuv, long monitorPixels[]);

#endif
