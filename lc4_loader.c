/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{
	FILE* file = fopen(file_name, "rb");
	return file;
}
//TODO: Shift bits to accommodate endianness
int parse_file (FILE* my_obj_file, row_of_memory** memory)
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
  
{
	unsigned short int address = 0x0;
	unsigned short int n = 0x0;

	//Word to be read into this array and stored
	unsigned short int word[4];

	while (fread(word,sizeof(unsigned short int),1, my_obj_file) != 0) {
		if (word[0] == 0xCADE || word[0] == 0xDADA) {
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			address = word[0];
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			n = word[0];
			for (int i = 0; i < n; i++) {
				fread(word, sizeof(unsigned short int), 1, my_obj_file);
				add_to_list(memory, address, word[0]);
				address++;
			}
		}else if (word[0] == 0xC3B7){
			char byte[4];
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			address = word[0];
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			n = word[0];
			char* label = malloc(n + 1);
			for (int i = 0; i < n; i++) {
				fread(byte, 1, 1, my_obj_file); //reading 1 byte
				label[i] = byte[0];
			}
			label[n] = '\0'; //null terminate

			/* Searching LinkedList Nodes to Update Label */
			//Ask: about double pointer logic here
			row_of_memory* node = search_address(*memory, address);
			if (node == NULL) {
				add_to_list(memory, address, 0);
				node = search_address(*memory, address);
				strcpy(node->label, label);
			}else{
				strcpy(node->label, label);
			}
			free(label);
		}
	}
	fclose(my_obj_file);
	return 0 ;
}

int shift_bits(unsigned short int array_element, unsigned short int result_array[50], int i)
{
	unsigned short int copy_a = array_element;
	//first shift
	copy_a = copy_a & 0x00FF;
	copy_a = copy_a << 8;

	//second shift
	unsigned short int copy_b = array_element;
	copy_b = copy_b & 0xFF00;
	copy_b = copy_b >> 8;

	unsigned short int result;

	result = copy_a + copy_b;
	result_array[i] = result;

	return (0);
}
