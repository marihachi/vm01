#ifndef VM01_DEBUG_H
#define VM01_DEBUG_H

#include "common.h"
#include "program.h"
#include "byteArray.h"

void Debug_printProgram(Program *program);

/**
 * @returns offset of the next instruction
*/
int Debug_printInst(Program *program, int instOffset);

void Debug_printBinaryDump(const ByteArray *byteArray);

#endif
