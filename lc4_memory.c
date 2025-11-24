/************************************************************************/
/* File Name : lc4_memory.c																							*/
/* Purpose   : This file implements the linked_list helper functions		*/
/* 							to manage the LC4 memory																*/
/*																																			*/
/* Author(s) : tjf and you																							*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>


/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list (row_of_memory** head,
									short unsigned int address,
									short unsigned int contents)
{
  /* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
	row_of_memory* curr = *head;
	while (curr) {
		if (curr->address == address) {
			curr->contents = contents;
			return (0);
		}
		curr = curr->next;
	}

  /* allocate memory for a single node */
	row_of_memory* new_node = malloc(sizeof(row_of_memory));
	if (new_node == NULL) {
		printf("Error allocating memory in add_to_list function");
		return (-1);
	}
	/* populate fields in newly allocated node w/ address&contents, NULL for label and assembly */
	/* do not malloc() storage for label and assembly here - do it in parse_file() and reverse_assemble() */
	new_node->address = address;
	new_node->contents = contents;
	new_node->label = NULL;
	new_node->assembly = NULL;
	new_node->next = NULL;

	/* if *head is NULL, node created is the new head of the list! */
	if (*head == NULL) {
		*head = new_node;
		new_node->next = NULL;
		return(0);
	}

	/* otherwise, insert node into the list in address ascending order */
	curr = *head;
	while (curr->next != NULL) {
		if ((curr->address < new_node->address) && (curr->next->address > new_node->address)) {
			new_node->next = curr->next;
			curr->next = new_node;
			return (0);
		}
		curr = curr->next;
	}
	//if curr is at end
	if (curr->next == NULL) {
		curr->next = new_node;
		curr->next->next = NULL;
		return(0);
	}
	free(new_node);

	/* return 0 for success, -1 if malloc fails */
	return 0 ;
}

void test(row_of_memory* head)
{
	if (head == NULL) {
		printf("Testing:Head is NULL");
		return;
	}
	printf("[address:contents:label]\n");
	while (head) {
		printf("[0x%x:0x%x:%s] -> ", head->address, head->contents, head->label);
		head = head->next;
	}
	if (head == NULL) {
		printf("NULL");
	}
};

/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
																short unsigned int address)
{
	/* traverse the linked list, searching each node for "address"  */
	if (head == NULL) {
		printf("Head passed into search_address is NULL");
		return NULL;
	}
	while (head) {
		if (head->address == address){
			return head;
		}
		head = head->next;
	}
	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if "address" isn't found */

	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
		                    				short unsigned int opcode)
{
  /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */
	/* see assignment instructions for a detailed description */
  if (head == NULL) {
  		printf("Head passed into search_opcode is null");
		return NULL;
  }
	short unsigned int opcode_lsb = opcode & 0x000F;

  /* traverse linked list until node is found with matching opcode in the most significant 4 bits
	AND "assembly" field of node is NULL */
	while (head) {
		if (head->assembly == NULL) {
			short unsigned int contents_msb = head->contents & 0xF000 >> 12;
			if (contents_msb == opcode_lsb) {
				return head;
			}
		}
		head = head -> next;
	}
  /* return pointer to node in the list if item is found */
  return NULL ;
}

/*
* print the full linked list
*/
void print_list (row_of_memory* head)
{
	/* make sure head isn't NULL */
	if (head == NULL) {
		printf("The list does not exist");
		return;
	}

	/* print out a header */


    
	/* traverse linked list, print contents of each node */

	return ;
}

/*
 * delete entire linked list
 */
int delete_list    (row_of_memory** head )
{
	/* delete entire list node by node */
	/* set the list head pointer to NULL upon deletion */

	return 0 ;
}
