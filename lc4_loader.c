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
#include "lc4_loader.h"

/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{
	FILE* file = fopen(file_name, "rb");
	return file;
}
int parse_file (FILE* my_obj_file, row_of_memory** memory)
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
  
{
	unsigned short int address = 0x0;
	unsigned short int n = 0x0;

	//Word to be read into this array and stored
	unsigned short int word[4] = {0};

	while (fread(word,sizeof(unsigned short int),1, my_obj_file) != 0) {
		word[0] = shift_bits(word[0]);
		//Code or Data
		if (word[0] == 0xCADE || word[0] == 0xDADA) {
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			address = shift_bits(word[0]);
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			n = shift_bits(word[0]);
			//Create Nodes that read in contents from .obj files
			for (int i = 0; i < n; i++) {
				fread(word, sizeof(unsigned short int), 1, my_obj_file);
				add_to_list(memory, address, shift_bits(word[0]));
				address++;
			}
			//Symbol

		}else if (word[0] == 0xC3B7){
			char byte[4];
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			address = shift_bits(word[0]);
			fread(word, sizeof(unsigned short int), 1, my_obj_file);
			n = shift_bits(word[0]);
			//allocate for label and add label letters
			char* label = malloc(n + 1);
			if (label == NULL) {
                free(label);
				printf("Error allocating memory in heap.");
				return (1);
			}
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
				node->label = malloc(n + 1);
				if (node->label == NULL) {
                    free(label);
					printf("Error allocating memory in heap");
					return (1);
				}
				strcpy(node->label, label);
			}else{
                if (node->label != NULL){
                    free(node->label);
                }
				node->label = malloc(n + 1);
				if (node->label == NULL) {
                    free(label);
					printf("Error allocating memory in heap.");
					return (1);
				}
				strcpy(node->label, label);
			}
			free(label);
		}
	}
	fclose(my_obj_file);
	return 0 ;
}

unsigned short int shift_bits(unsigned short int array_element)
{
	unsigned short int copy_a = array_element;
	//first shift
	copy_a = copy_a & 0x00FF;
	copy_a = copy_a << 8;

	//second shift
	unsigned short int copy_b = array_element;
	copy_b = copy_b & 0xFF00;
	copy_b = copy_b >> 8;

	unsigned short int result = copy_a + copy_b;
	return result;
}
