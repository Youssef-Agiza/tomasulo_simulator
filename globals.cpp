#include "globals.hpp"
#include "mem.hpp"
#include "regs.hpp"

ushort regs[REGFILE_SIZE];
uint mem[MEMORY_SIZE];
std::vector<instruction> inst_mem;
struct RegStat regstat[REGFILE_SIZE];

std::deque<struct CDB> cdb;

int PC = 0;
int cycles = 0;
bool stall=false;