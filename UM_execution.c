/*
 * Filename: UM_execution.c
 * Creators: Taylor Ampatiellos and Sarah Hall-Swan
 * Date: April 15th, 2016
 *
 * Purpose: Keeps track of the registers. Loops through the inputted
 * 	    program and calls all of the instruction functions.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "UM_execution.h"
#include "UM_instructions.h"
#include "UM_seg_abstraction.h"

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, MAP, UNMAP, OUT, IN, LOADP, LV
} Um_opcode;

/* Assembles 32-bit words from the input file data. */ 
uint32_t make_word(FILE *input);

/* Returns the opcode of a given word. */
static uint32_t get_opcode(uint32_t word);

/* Returns a specific register from a given word using the MSB of the register
 * in the word as an offset. 
 */ 
static uint32_t get_register(uint32_t word, int offset);

void execute_instructions(FILE *input)
{
	Stack_T seg_ids = Stack_new(); 
	Seq_T seg_mem = Seq_new(0);
	uint32_t regs[8];
	Segment seg_zero = malloc(sizeof(struct Segment));	
	seg_zero->arr = malloc(10 * sizeof(uint32_t));
	seg_zero->size = 10;	

	uint32_t A, B, C, ra, rb, rc, opcode, instruction, counter;
	
	seg_zero = initialize_UM(regs, input, seg_zero);
	Seq_addlo(seg_mem, seg_zero);
	
	for (counter = 0; counter < seg_zero->size; counter++) {		
		instruction = seg_zero->arr[counter];
		ra = get_register(instruction, 9);
		rb = get_register(instruction, 6);
		rc = get_register(instruction, 3);
		opcode = get_opcode(instruction);
		assert(opcode < 14);
		A = regs[ra]; 				
		B = regs[rb];
		C = regs[rc];
		switch (opcode) {
		        case CMOV:   regs[ra] = conditional_move(A, B, C);
		        break;
		        case SLOAD:  regs[ra] = segmented_load(C, B, seg_mem);
		        break;
		        case SSTORE: segmented_store(B, C, A, seg_mem);
		        break;
		        case ADD:    regs[ra] = add(B, C);
			break;
		        case MUL:    regs[ra] = multiply(B, C);
			break;
		        case DIV:    regs[ra] = divide(B, C);
		        break;
		        case NAND:   regs[ra] = nand(B, C);
		        break;
		        case HALT:   halt(seg_zero, seg_mem, seg_ids);
				     return;
			case MAP:    regs[rb] = map_seg(seg_mem, C, seg_ids);
		        break;
			case UNMAP:  assert(C != 0);
				     unmap_seg(seg_mem, C);
				     uint32_t *id = malloc(sizeof(uint32_t));
				     *id = C;
				     Stack_push(seg_ids, id);
			break;
			case OUT:    output(C);
		        break;
        		case IN:     regs[rc] = get_input();
		        break;
			case LOADP:  if (B != 0) {
					     seg_zero = load_prog(B, seg_mem);
					     unmap_seg(seg_mem, 0);
					     Seq_put(seg_mem, 0, seg_zero);
				     }
				     counter = C - 1;
		        break;
			case LV:     ra = get_register(instruction, 28);
				     regs[ra] = load_value(instruction);
			break;
		}
	}
}

Segment initialize_UM(uint32_t regs[], FILE *input, Segment seg_zero)
{
	uint32_t word;
	int i;
	uint32_t c = 0;
	for (i = 0; i < 8; i++) {
		regs[i] = 0;
	}

	word = make_word(input);

	while (word != (unsigned)EOF) {
		if (c >= seg_zero->size)
			seg_zero->arr = realloc(seg_zero->arr, 4 * 2 * c);
		seg_zero->arr[c] = word;
		c++;
		word = make_word(input);
	}

	seg_zero->size = c;
	return seg_zero;
}

uint32_t make_word(FILE *input)
{
	uint32_t a, b, c, d;
	a = getc(input);
	b = getc(input);
	c = getc(input);
	d = getc(input);

	a = a << 24;
	b = b << 16;
	c = c << 8;

	return (a | b | c | d);
}

uint32_t get_opcode(uint32_t word)
{
	return word >> 28;
}

uint32_t get_register(uint32_t word, int offset)
{
	word = word << (32 - offset);
	word = word >> 29;
	return word;
}
