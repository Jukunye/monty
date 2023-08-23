0x19. C - Stacks, Queues - LIFO, FIFO

Monty Program
=====================================


Introduction
------------

The Monty program is an interpreter for a stack-based programming language.
It reads Monty bytecode files containing instructions and performs stack operations accordingly. This documentation provides an overview of the program's structure, main components, and functions.

## Table of Contents
1. [Program_Overview](#program_overview)
2. [Data_Structures](#data_structures)
3. [Main_Function](#main_function)
4. [Read_file](#read_file)
5. [Tokenization](#tokenization)
6. [Operations](#operations)
7. [Memory_Management](#memory_management)
8. [Conclusion](#conclusion)

## Program_Overview

The Monty program reads and interprets Monty bytecode files line by line.
It executes various stack manipulation and arithmentic operation based on the instruction in the bytecode. The program utilizes a doubly linked list to implement the stack, where nodes contain integers.
- Usage: `monty file`
    - where `file` is the path to the file containing Monty byte code

## Data_Structures
### `stack_t` Structure
- Represents a node in the stack.
- Contatins:
    - `int n`: Integer value stored in the node.
    - `struct stack_s *prev`: Pointer to the previous node in the stack.
    - `struct stack_s *next`: pointer to the next node in the stack.
```
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

```
### `instruction_t` Structure
- Represetns an instruction to be executed.
- Contains:
    - `char *opcode`: Name of the instruction.
    - `void (*f)(stact_t **stack, unsigned int line_number)`: pointer to the function that implements the instruction.
```
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

```
## Main_Function
`int main(int argc, char **argv)`
- Entry point of the program.
- Parses command line arguments to get the input bytecode file path.
- Calls the `read_file` function to process the bytecode file.

## Read_file
`void read_file(char *pathname)`
- Reads the content of a file specified by the `pathname`.
- Reads the file line by line by calling the `getline` function in a loop until the end of file is reached (`getline` returns `-1`) 
- processes each line by tokenizing using the `tokenize` function.
- Calls the `operations` function to perform stack operations based on instructions.

## Tokenization
### `tokenize` Function
`char **tokenize(char *line)`
- Splits a string into an array of tokens based on delimiter characters.
- Returns a dynamically allocated array of strings(tokens).
- Utilizes the `strtok` function to split the string.

## Operations
### `operations` Function
- Executes the appropriate operation based on the given opcode.
- Compares the opcode with a predefined list of instructions and their associated functions.
- If a matching opcode is found, the associated function is called with the stack and line number.

#### Supported Instructions
- `push`: Pushes an integer onto the stack.
- `pall`: prints all elements in the stack.
- `pint`: Prints the value at the top of the stack.
- `pop`: Removes the top element from the stack.
- `swap`: Swaps the two elements of the stack.
- `add`: Adds the top two elements of the stack.
- `nop`: No operation (does nothng).
- `sub`: Subtracts the top element from the second element in the stack.
- `mul`: Multiplies the top two elements of the stack.
- `mod`: Computes the modulus of the second element by the top element in the stack.

## Memory_Management
- The program utilizes dynamic memory allocation for creating nodes and arrays of tokens.
- Memory is properly freed to prevent memory leaks using functions like `free_list`, `free_array`, and `free`.

## Conclusion
The Monty program is a simple interpreter that reads and processes Monty bytecode files. It utilizes a stack data structure and supports various stack manipulation and arithmentic operations. This documentation provides an overview of the program's components and functionality to help undestand its implementation.

**Authors: [ Jukunye Shira,  Festus Kibet ]**
