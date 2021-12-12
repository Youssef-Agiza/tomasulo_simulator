#include "globals.hpp"
<<<<<<< HEAD

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
int PC = 0;
int cycles = 0;
bool stall = false;
bool finished = false;
bool issued_branch = false;
=======
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
>>>>>>> 36bc7d1f224494750c3028f84d6935611f593660
