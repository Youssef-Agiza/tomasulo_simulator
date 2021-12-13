#include "globals.hpp"

// regs.hpp
ushort regs[REGFILE_SIZE];
struct RegStat regstat[REGFILE_SIZE];

// mem.hpp
uint mem[MEMORY_SIZE];
std::vector<instruction> inst_mem;

// cdb.hpp
bool cdb::available = true;
ushort cdb::rd = -1;
rs *cdb::st = nullptr;

// globals.hpp
std::deque<rs *> load_store_buffer;
int PC = 0;
int cycles = 0;
bool stall = false;
bool finished = false;
bool issued_branch = false;
