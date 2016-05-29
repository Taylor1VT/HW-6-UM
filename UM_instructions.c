/*
 * Filename: UM_instructions.c
 * Creators: Taylor Ampatiellos and Sarah Hall-Swan
 * Date: April 15th, 2016
 *
 * Purpose: Instructions to be executed by the UM.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>

#include "UM_instructions.h"
#include "UM_seg_abstraction.h"

uint32_t conditional_move(uint32_t A, uint32_t B, uint32_t C)
{	
	if (C != 0)
		return B;
	
	return A;
}

uint32_t segmented_load(uint32_t offset, uint32_t id, Seq_T memory)
{
	return load_word(offset, id, memory);
}

void segmented_store(uint32_t offset, uint32_t word, uint32_t id, Seq_T memory)
{
	store_word(offset, word, id, memory);
}

uint32_t add(uint32_t B, uint32_t C)
{
	return (B + C);
}

uint32_t multiply(uint32_t B, uint32_t C)
{
	return (B * C);
}

uint32_t divide(uint32_t B, uint32_t C)
{
	assert(C != 0);
	return (B / C);
}

uint32_t nand(uint32_t B, uint32_t C)
{
	return ~(B & C);
}

void halt(Segment seg_zero, Seq_T seg_mem, Stack_T seg_ids)
{
	int i;
	(void)seg_zero;
	Segment current;
	for (i = 0; i < Seq_length(seg_mem); i++) {
		current = Seq_get(seg_mem, i);
		if (current != NULL) {
			free(current->arr);
			free(current);
		}
	}
	Seq_free(&seg_mem);
	while (Stack_empty(seg_ids) == 0) {
		free(Stack_pop(seg_ids));
	}	
	
	Stack_free(&seg_ids);
}

uint32_t map_seg(Seq_T memory, uint32_t size, Stack_T seg_ids)
{	
	return map(memory, size, seg_ids);
}

void unmap_seg(Seq_T memory, uint32_t id)	
{
	unmap(memory, id);
}

void output(uint32_t C)
{
	assert(C <= 255);	
	putchar(C);
}

uint32_t get_input()
{
	int input = getchar();

	if (input == EOF)
		return ~0;
	else
		return (uint32_t)input;
}

Segment load_prog(uint32_t id, Seq_T memory)
{
	Segment dup_segment, seg;
	uint32_t i;

	seg = Seq_get(memory, id);
	assert(seg != NULL);

	dup_segment = malloc(sizeof(struct Segment));
	dup_segment->arr = malloc(seg->size * 4);
	dup_segment->size = seg->size;

	for (i = 0; i < seg->size; i++) {
		dup_segment->arr[i] = seg->arr[i];
	}

	return dup_segment;
}

uint32_t load_value(uint32_t word)
{
	return (word << 7) >> 7;
}


