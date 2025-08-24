#ifndef FuncDeclaration_H
#define FuncDeclaration_H

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 500
#define MAX_LABEL 50
#define HEX_CODE 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Label {
	char name[MAX_LABEL];
	char line_num[12];
	struct Label* next_L;
} Label;

typedef struct line {
	char opcode[8];
	char rd[6];
	char rs[6];
	char rt[6];
	char rm[6];
	char imm1[12];
	char imm2[12];
//	struct Line* next;
} Line;

Label* label_init(char name[50], int line_num);
void line_init(Line* dest, char opcode[], char rd[], char rs[], char rt[], char rm[], char imm1[], char imm2[]);
void add_label(Label* head, Label* new_L);

void linetohexconvert(Line* line);

void lineToCode(char inpt_line[MAX_LINE], Line* inst_line);

void getWord(char line[MAX_LINE], int *pI, char reg[MAX_LINE]);

void opcodeConvert(char opcode[MAX_LINE], char opcodeHex[HEX_CODE]);

void regCodeConvert(char reg[MAX_LINE], char regcodeHex[HEX_CODE]);

void immCodeConvert(char imm[500], char immHex[4]);

// First pass functions:
void tabs_remove(char line[]);
int is_label(char line[]);
int is_dot_word(char line[]);
void first_pass(FILE* program, Label* head);

//second pass functions:
void label_finder(Line* line, Label* header);
void data_mem_init(char data_mem[][9]);
int store_word(char data_mem[][9], char curr_line[], int max_ind);
void imem_write(FILE* imemin, Line* inst_mem, Label* header, int inst_len);
void dmem_write(FILE* dmemin, char data_mem[][9]);
int second_pass(FILE* program, Line* inst_mem, char data_mem[][9]);

#endif