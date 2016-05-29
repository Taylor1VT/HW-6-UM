/*
 * Filename: UM_execution.h
 * Creators: Taylor Ampatiellos and Sarah Hall-Swan
 * Date: April 5th, 2016
 *
 * Purpose: Interface for UM_execution.c
 */

#ifndef UM_EXECUTION
#define UM_EXECUTION

#include <stdlib.h>
#include <stdint.h>
#include "UM_seg_abstraction.h"

/* Initializes segment zero and all memory storage units needed for
 * the UM to run. Uses a for loop and switch statement to execute the
 * instructions from the input program.
 */
void execute_instructions(FILE *input);

/* Initializes the registers to be used by the UM. Reads in instructions
 * from the input program and stores them in segment zero until EOF.
 */
Segment initialize_UM(uint32_t registers[], FILE *input, Segment seg_zero);

#endif
