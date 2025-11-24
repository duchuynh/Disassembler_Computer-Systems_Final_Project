/************************************************************************/
/* File Name : lc4_disassembler.c																				*/
/* Purpose   : This file implements the reverse assembler								*/
/*							for LC4 assembly.  It will be called by main()					*/
/*																																			*/
/* Author(s) : tjf and you																							*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lc4_memory.h"




int parse_reg(unsigned short int reg_binary, char reg[]) {
	switch (reg_binary) {
		case 000:
			strcpy(reg, "R0");
			break;
		case 001:
			strcpy(reg, "R1");
			break;
		case 010:
			strcpy(reg, "R2");
			break;
		case 011:
			strcpy(reg, "R3");
			break;
		case 100:
			strcpy(reg, "R4");
			break;
		case 101:
			strcpy(reg, "R5");
			break;
		case 110:
			strcpy(reg, "R6");
			break;
		case 111:
			strcpy(reg, "R7");
			break;
	}
	return (0);
}
//TODO: ADD IMMEDIATE
int get_mnemonic(unsigned short int sub_opcode, char mnemonic[]) {
	switch (sub_opcode) {
		case 000:
			strcpy(mnemonic, "ADD");
			break;
		case 001:
			strcpy(mnemonic, "MUL");
			break;
		case 010:
			strcpy(mnemonic, "SUB");
			break;
		case 011:
			strcpy(mnemonic, "DIV");
			break;
	}
	return (0);
}
/*
 * Returns entire assembly line
 */
char* parse_contents(unsigned short int contents) {
	//0001010001001001
	char instruction[100];

	char mnemonic[4] = {0};
	char rd[3] = {0};
	char rs[3] = {0};
	char rt[3] = {0};

	parse_reg(contents & 0000111000000000 >> 9, rd);
	parse_reg(contents & 0000000111000000 >> 6, rs);
	parse_reg(contents & 0000000000000111, rt);
	get_mnemonic(contents & 0000000000111000 >> 3, mnemonic);
	strcpy(instruction, mnemonic);
	strcat(instruction, rd);
	strcat(instruction, rs);
	strcat(instruction, rt);
	//TODO: Malloc array return
	return instruction;
}

int reverse_assemble (row_of_memory* memory)
{
	/* if you use binary constants, they should be proceeded by a 0b as in 0b011 for decimal 3 */
	/* without the 0b, constants with leading zeroes will be considered octal constants, not binary */
	/* hex constants starting with 0x can also be used */

	unsigned short int code_start = 0x0000;
	unsigned short int code_end = 0x1FFF;

	row_of_memory* node;
	while ((node = search_opcode(memory, 0x0001)) != NULL) {

		//Check Code Region Validity
		if (node->address >= code_start && node->address <= code_end) {

			char* assembly = parse_contents(node->contents);
			//node->assembly = malloc(sizeof())
		}
	}
	return 0 ;
}

