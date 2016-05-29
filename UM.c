/*
 * Filename: UM.c
 * Creators: Taylor Ampatiellos and Sarah Hall-Swan
 * Date: April 15th, 2016
 *
 * Purpose: The main function for the UM emulator.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <except.h>

#include "UM_execution.h"

int main(int argc, char *argv[])
{
        if (argc != 2) {
		fprintf(stderr, "Usage: [filename]\n");
		exit(EXIT_FAILURE);
	}

        FILE *fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		fprintf(stderr, "invalid filename\n");
		exit(EXIT_FAILURE);
	}

        execute_instructions(fp);
        fclose(fp);
}
