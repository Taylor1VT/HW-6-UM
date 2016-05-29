+----------------------------------------+
|              README - HW6              |
| Sarah Hall-Swan and Taylor Ampatiellos |
| 4/15/16				                         |
+----------------------------------------+
									     80
Acknowledgements:
Thank you Comp40 staff!

Hours Spent:
analyzing the assignment: 1 hr 
preparing the design:     3.5 hrs
solving the problems:	  16 hrs

This program is an emulator for a UM that implements the following
instructions as described in the specifications:
	conditional move, segmented load, segmented store, addition,
	multiplication, division, bitwise NAND, halt, map segment,
	unmap segment, output, input, load program, load value

Included Files:
	UM.c -
		Contains the main function that opens the file.
	UM_execution.h / UM_execution.c - 
		Contains the functions for running the UM emulator, looping
		through the inputed UM program, and controlling the registers.
	UM_instruction.h / UM_instructions.c - 
		Contains a function for each of the 14 UM instructions, 
		performs their operations.
	UM_seg_abstraction.h / UM_seg_abstraction.c - 
		Contains the functions for manipulating the segmented memory
		i.e. mapping and unmapping segments, and loading words 
		from segments.
	Makefile / compile - 
		Makes executable um binary
	UMTESTS -
		lists the names of each .um unit test file

Architecture:
	UM_execution.c calls functions from UM_instructions.c to perform the
	instructions. If the instruction calls for manipulating a segment of
	memory, the UM_instruction function calls a function from
	UM_seg_abstraction. UM_execution.c creates and has access to the
	sequence of segments and the stack of reusable segment ids
	to pass to the relevant functions.
	

Departures from design:
	The only major departure from the initial design is the data types
	used the store the segmented memory. Initially, we were planning 
	on using a Hanson Table to keep track of segments. Now the memory 
	is stored in dynamic arrays stored in a sequence. The segment ids 
	that can be reused are stored in a stack.

How long it takes our program to execute 50 million instructions:
	The provided benchmark test "midmark.um" executes 85,070,522 
	instructions in 2.76 seconds. Thus, it takes our program 
	roughly 1.62 seconds to execute 50 million instructions.

UM unit tests:
	add.um: Tests the add, load value, output, and halt instructions.
		Loads two numbers, 48 and 6, into registers, adds them, then
			outputs the result (ASCII: 6). Halts the program.
 
	divide.um: Tests the divide, load value, output, and halt instructions.
		   Loads two numbers, 54 and 1, into registers, divides them,
			then outputs the result (ASCII: 6). Halts the program.

	halt-verbose.um: Tests the halt instruction. Halts the program. Outputs
				"Bad!\n" if the program does not halt.

	input.um: Tests the input, output, and halt instructions.
		  Reads in a character 'T' from stdin (from input.0), then
			outputs this character. Halts the program.

	load-program.um: Tests the load value, load program, and halt
				instructions.
			 Loads the program from segment zero with a new counter
				value. Halts the program. Outputs "Bad!\n" if
				the program fails to load properly.

	load-store.um: Tests the load value, segmented store, segmented load, 
				output, and halt functions. 
		       Loads a value into a register and stores that value 
				into segment 0. Then loads a value from 
				segment zero at the same offset and outputs 
				the result (ASCII: !)
				Halts the program.

	map.um: Tests the map, load, store, and halt functions.
		Maps a segment, stores and loads a word into and from that
		segment. Halts the program without unmapping, to test if 
		the halt function frees all memory.

	map-unmap.um: Tests the map, segmented load, store, unmap, and 
		      halt functions. Maps a segment, stores and loads
		      a word into and from that segment, then unmaps 
		      the segment. Halts the program.

	multiply.um: Tests the load value, multiply, output, and halt
		     instructions.
		     Loads values into registers, then multiplies them.
		     Outputs the result (ASCII: ÿ) and halts the program.

	nand.um: Tests the load value, nand, output, and halt
		     instructions.
		 Loads 4 values into registers, nands them in pairs, then
		 the results together. Outputs the result (ACSII: ~) and
		 halts the program.

	will-move.um: Tests the load value, conditional move, output, and
		      halt instructions.
		      Loads 1 into a register, and another value into
	              another register, then performs a conditional move
		      with 1 as the condition, so the move occurs. Outputs
		      the result (ASCII 5) and halts the program.

	wont-move.um: Tests the load value, conditional move, output, and
		      halt instructions.
		      Values into two registers, then performs a conditional
		      move with 0 as the condition, so the move doesn't 
		      occur. Outputs the result (ASCII &) and halts the 
		      program. If the output is ASCII 5, the move failed.
