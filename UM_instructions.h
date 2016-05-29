/*
 * Filename: UM_instructions.h
 * Creators: Taylor Ampatiellos and Sarah Hall-Swan
 * Date: April 15th, 2016
 *
 * Purpose: Interface for UM_instructions.c
 */

#ifndef UM_INSTRUCTIONS
#define UM_INSTRUCTIONS

#include <stdlib.h>
#include <stdint.h>
#include <seq.h>
#include <stack.h>

#include "UM_seg_abstraction.h"

/* Only executes move if C != 0. */
uint32_t conditional_move(uint32_t A, uint32_t B, uint32_t C); 

/* Loads word from memory. */
uint32_t segmented_load(uint32_t offset, uint32_t id, Seq_T memory);

/* Stores word into memory. */
void segmented_store(uint32_t offset, uint32_t word, uint32_t id, Seq_T mem);

/* Adds two values. */
uint32_t add(uint32_t B, uint32_t C);

/* Multiplies two values. */
uint32_t multiply(uint32_t B, uint32_t C); 

/* Divides two values. */ 
uint32_t divide(uint32_t B, uint32_t C); 

/* Nands two values. */
uint32_t nand(uint32_t B, uint32_t C); 

/* Frees all memory that still exists. Terminates the UM. */
void halt(Segment seg_zero, Seq_T seg_mem, Stack_T seg_ids);

/* Activates a new segment. Returns the ID of said segment. */
uint32_t map_seg(Seq_T memory, uint32_t size, Stack_T seg_ids);  //added stack

/* Deactivates a segment. */
void unmap_seg(Seq_T memory, uint32_t id); 

/* Outputs a given character. Fails if the character is > 255. */
void output(uint32_t C); 

/* Gets input from stdin. If EOF is signaled, returns ~0. */
uint32_t get_input(); 

/* Duplicates a segment and returns the duplicate. */
Segment load_prog(uint32_t id, Seq_T memory);

/* Returns the 25 least-significant-bits of the word. */
uint32_t load_value(uint32_t word); 

#endif
