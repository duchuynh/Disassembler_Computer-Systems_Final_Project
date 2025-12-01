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
		case 0b000:
			strcpy(reg, "R0");
			break;
		case 0b001:
			strcpy(reg, "R1");
			break;
		case 0b010:
			strcpy(reg, "R2");
			break;
		case 0b011:
			strcpy(reg, "R3");
			break;
		case 0b100:
			strcpy(reg, "R4");
			break;
		case 0b101:
			strcpy(reg, "R5");
			break;
		case 0b110:
			strcpy(reg, "R6");
			break;
		case 0b111:
			strcpy(reg, "R7");
			break;
	}
	return (0);
}
//TODO: ADD IMMEDIATE
int get_mnemonic(unsigned short int sub_opcode, char mnemonic[]) {
	switch (sub_opcode) {
		case 0b000:
			strcpy(mnemonic, "ADD ");
			break;
		case 0b001:
			strcpy(mnemonic, "MUL ");
			break;
		case 0b010:
			strcpy(mnemonic, "SUB ");
			break;
		case 0b011:
			strcpy(mnemonic, "DIV ");
			break;
	}
	return (0);
}
int get_imm(unsigned short int imm_bin, char mnemonic[]) {

	switch (imm_bin) {
		case 0b00000:
			strcpy(mnemonic, "#0");
			break;
		case 0b00001:
			strcpy(mnemonic, "#1");
			break;
		case 0b00010:
			strcpy(mnemonic, "#2");
			break;
		case 0b00011:
			strcpy(mnemonic, "#3");
			break;
		case 0b00100:
			strcpy(mnemonic, "#4");
			break;
		case 0b00101:
			strcpy(mnemonic, "#5");
			break;
		case 0b00110:
			strcpy(mnemonic, "#6");
			break;
		case 0b00111:
			strcpy(mnemonic, "#7");
			break;
		case 0b01000:
			strcpy(mnemonic, "#8");
			break;
		case 0b01001:
			strcpy(mnemonic, "#9");
			break;
		case 0b01010:
			strcpy(mnemonic, "#10");
			break;
		case 0b01011:
			strcpy(mnemonic, "#11");
			break;
		case 0b01100:
			strcpy(mnemonic, "#12");
			break;
		case 0b01101:
			strcpy(mnemonic, "#13");
			break;
		case 0b01110:
			strcpy(mnemonic, "#14");
			break;
		case 0b01111:
			strcpy(mnemonic, "#15");
			break;
		case 0b10000:
			strcpy(mnemonic, "#-16");
			break;
		case 0b10001:
			strcpy(mnemonic, "#-15");
			break;
		case 0b10010:
			strcpy(mnemonic, "#-14");
			break;
		case 0b10011:
			strcpy(mnemonic, "#-13");
			break;
		case 0b10100:
			strcpy(mnemonic, "#-12");
			break;
		case 0b10101:
			strcpy(mnemonic, "#-11");
			break;
		case 0b10110:
			strcpy(mnemonic, "#-10");
			break;
		case 0b10111:
			strcpy(mnemonic, "#-9");
			break;
		case 0b11000:
			strcpy(mnemonic, "#-8");
			break;
		case 0b11001:
			strcpy(mnemonic, "#-7");
			break;
		case 0b11010:
			strcpy(mnemonic, "#-6");
			break;
		case 0b11011:
			strcpy(mnemonic, "#-5");
			break;
		case 0b11100:
			strcpy(mnemonic, "#-4");
			break;
		case 0b11101:
			strcpy(mnemonic, "#-3");
			break;
		case 0b11110:
			strcpy(mnemonic, "#-2");
			break;
		case 0b11111:
			strcpy(mnemonic, "#-1");
			break;
	}
	return 0;

}
/*
 * Returns entire assembly line as an array
 */
char* parse_contents(unsigned short int contents) {
	//0001010001001001
	char* instruction = NULL;
	//TODO: FREE
	instruction = malloc(sizeof(char)* 20);
	if (instruction == NULL) {
		printf("Error allocating memory for the instruction in parse_contents.");
	}

	char mnemonic[5] = {0};
	char rd[5] = {0};
	char rs[5] = {0};
	char rt[5] = {0};

	if ((contents & 0b0000000000100000) >> 5 == 0x0) {
		unsigned short int sub_opcode = (contents & 0b0000000000111000) >> 3;
		get_mnemonic(sub_opcode, mnemonic);
		parse_reg((contents & 0b0000000000000111), rt);
	} else if ((contents & 0b0000000000100000) >> 5 == 0x1) {
		strcpy(mnemonic, "Add ");
		get_imm(contents & 0b0000000000011111, rt);
	}

	parse_reg((contents & 0b0000111000000000) >> 9, rd);
	//rd and rs need to have a comma and space.
	rd[2] = ',';
	rd[3] = ' ';
	rd[4] = '\0';

	parse_reg((contents & 0b0000000111000000) >> 6, rs);
	//rd and rs need to have a comma and space.
	rs[2] = ',';
	rs[3] = ' ';
	rs[4] = '\0';
	strcpy(instruction, mnemonic);
	strcat(instruction, rd);
	strcat(instruction, rs);
	strcat(instruction, rt);
	return instruction;
}

int reverse_assemble (row_of_memory* memory)
{
	/* if you use binary constants, they should be proceeded by a 0b as in 0b011 for decimal 3 */
	/* without the 0b, constants with leading zeroes will be considered octal constants, not binary */
	/* hex constants starting with 0x can also be used */

	unsigned short int code_start = 0x0000;
	unsigned short int code_end = 0x1FFF;
	unsigned short int os_code_start = 0x8000;
	unsigned short int os_code_end = 0x9FFF;

	row_of_memory* node = memory;
	while ((node = search_opcode(node, 0x0001)) != NULL) {

		//Check Code Region Validity
		if ( ((node->address >= code_start    && node->address <= code_end) ||
		  (node->address >= os_code_start && node->address <= os_code_end)) && node->assembly == NULL ) {

			//get the instruction string
			char* instruction = parse_contents(node->contents);
			node->assembly = instruction;
			}
		else
		{
			node = node->next;
		}
	}
	return 0;
}

