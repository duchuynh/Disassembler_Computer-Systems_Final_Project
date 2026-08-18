This is the final project for Penn's Intro to Computer Systems course.

# Overview
This project focused on dynamic memory management of Linkedlists using C. Given .obj(binary) files in the obj_files_for_student_testing folder, the program takes the machine code from each of the .obj files, parses them, and converts them to assembly code, and finally creates Linkedlist structs that stores the machine code and assembly code into each node of the linkedlist.
The make build system was used to automate the task of compiling and running the code.

# Features
Little Computer-4 (LC4) Loader - Loads .obj files, parses the machine code from the files, and creates or modify Linked List nodes based on the instructions. The parsing follows a specific non-ASCII header format from the course. node of the linkedlist represents a single row in memory.

Disassembler - Translates all nodes with arithmetic 16-bit hexadecimal instructions into their assembly code equivalent. Following this, the assembly instructions are inserted as a data attribute in the node.

In the parse_file method, we take the machine code from the .obj file, shift the bits to ensure correct endianness and transfer the machine code into a node as one of its attributes.

Later on in parse_contents, we translate the machine instructions by using case statements to transfer the hexadecimal representations into decimal and digit string representations.

<img width="465" height="120" alt="image" src="https://github.com/user-attachments/assets/2529c8e8-5f43-4efd-b490-652c025042b8" />

Freeing memory - All allocated dynamic memory is freed before the conclusion of the program.

Through completion of this project, I learned pointer management of the heap, allocations of dynamic memory, binary code parsing, and string manipulations in C.
For example, creating new instances of nodes using structs (classes in C) was good practice for objects and classes and pointer management. We used a double pointer to iterate through each of the single pointer locations in memory to check for specific opcodes or if a memory location is already instantialized and being used.


