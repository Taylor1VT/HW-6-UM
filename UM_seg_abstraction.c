/*
 * Filename: UM_seg_abstraction.c
 * Creators: Taylor Ampatiellos and Sarah Hall-Swan
 * Date: April 15th, 2016
 *
 * Purpose: Creates/releases/accesses the segmented memory. 
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <math.h>

#include "UM_seg_abstraction.h"

uint32_t map(Seq_T memory, int size, Stack_T seg_ids)
{
	Segment seg = malloc(sizeof(struct Segment));
	seg->arr = malloc(size * 4);
	seg->size = size;

	int i;
	for(i = 0; i < size; i++) {
		seg->arr[i] = 0;
	}
	uint32_t id;
	if (Stack_empty(seg_ids) == 1) {
		id = Seq_length(memory);
		Seq_addhi(memory, seg);
	} else {
		uint32_t *idp = Stack_pop(seg_ids);
		id = *idp;

		Seq_put(memory, id, seg);
		free(idp);
	}
	return id;
}

void unmap(Seq_T memory, uint32_t id)	
{
	Segment seg;

	seg = Seq_put(memory, id, NULL);
	assert(seg != NULL);	
	free(seg->arr);	
	free(seg);
}

uint32_t load_word(uint32_t offset, uint32_t id, Seq_T memory)
{
	Segment seg;
	
	seg = Seq_get(memory, id);
	assert(seg != NULL);
	assert(offset < seg->size);	

	return seg->arr[offset];
}

void store_word(uint32_t offset, uint32_t word, uint32_t id, Seq_T memory)
{
	Segment seg;
	
	seg = Seq_get(memory, id);

	assert(seg != NULL);
	assert(offset < seg->size);
	seg->arr[offset] = word;		
}

