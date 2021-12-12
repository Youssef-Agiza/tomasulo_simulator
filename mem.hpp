#ifndef MEM_H
#define MEM_H
#include "common.hpp"
#include "instruction.hpp"

#define ADDRESS_SIZE 16
#define MEMORY_SIZE (2 << ADDRESS_SIZE)

extern std::vector<instruction> inst_mem;
extern uint data_memory[MEMORY_SIZE];

#endif