This is the final project for Penn's Intro to Computer Systems course.

# Overview
This project focused on dynamic memory management of Linkedlists using C. Given .obj(binary) files in the obj_files_for_student_testing folder, the program takes the machine code from each of the .obj files, parses them, converts them to assembly code, and finally creates Linkedlist structs that stores the machine code and assembly code into each node of the linkedlist.
The make Build System was used to automate the task of compiling and running the code.

# Features
Little Computer-4 (LC4) Loader - Loads .obj files, parses the machine code from the files, and creates or modify Linked List nodes based on the instructions. The parsing follows a specific non-ASCII header format from the course.

Disassembler - Translates all nodes with arithmetic 16-bit hexadecimal instructions into their assembly code equivalent. Following this, the assembly instructions are inserted as a data attribute in the node.

<img width="465" height="120" alt="image" src="https://github.com/user-attachments/assets/2529c8e8-5f43-4efd-b490-652c025042b8" />



Freeing memory - All allocated dynamic memory is freed before the conclusion of the program.

Through completion of this project, I learned pointer management of the heap, allocations of dynamic memory, binary code parsing, and string manipulations in C.

