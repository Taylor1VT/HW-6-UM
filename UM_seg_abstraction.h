/*
 * Filename: UM_seg_abstraction.h
 * Creators: Taylor Ampatiellos and Sarah Hall-Swan
 * Date: April 5th, 2016
 *
 * Purpose: Interface for UM_seg_abstraction.c
 */

#ifndef UM_SEG_ABSTRACTION
#define UM_SEG_ABSTRACTION

#include <stdlib.h>
#include <stdint.h>
#include <table.h>
#include <seq.h>
#include <stack.h>

typedef struct Segment {
	uint32_t size;
	uint32_t *arr;
} *Segment;


/* Creates a new array of length “size" and initializes to 0, then check if 
 * there are any ids to be reused in the stack, and stores in the
 * sequence at that index, or at the end of the sequence.
 * Returns the segment id.
 */
uint32_t map(Seq_T memory, int size, Stack_T seg_ids);

/* Frees the array at index “id” of the sequence, and sets the element at 
 * that index equal to NULL
 */
void unmap(Seq_T memory, uint32_t id);	

/* Returns the word at the segment “id” at offset “offset”, by accessing the
 * sequence at index “id” and returning the value at the array at offset.
 */
uint32_t load_word(uint32_t offset, uint32_t B, Seq_T memory);

/* Puts the word in the segment by storing it in index “offset” of the array
 * in the sequence at index “id”.
 */
void store_word(uint32_t offset, uint32_t word, uint32_t id, Seq_T memory);

#endif
