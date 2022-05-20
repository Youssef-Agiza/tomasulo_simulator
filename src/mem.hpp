#ifndef MEM_H
#define MEM_H
#include "common.hpp"
#include "instruction.hpp"

#define ADDRESS_SIZE 16
#define MEMORY_SIZE (2 << 7)

extern std::vector<instruction> inst_mem;
extern uint data_mem[MEMORY_SIZE];
// extern std::vector<uint> data_mem;
#endif