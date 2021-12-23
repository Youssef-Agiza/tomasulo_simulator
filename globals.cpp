#include "globals.hpp"

// regs.hpp
short regs[REGFILE_SIZE] = {0};
struct RegStat regstat[REGFILE_SIZE];
struct RegStat regstat_copy[REGFILE_SIZE];

// mem.hpp
std::vector<uint> data_mem(MEMORY_SIZE, 0);
// uint data_mem[MEMORY_SIZE];
std::vector<instruction> inst_mem;

// cdb.hpp
bool cdb::available = true;
short cdb::rd = -1;
rs *cdb::st = nullptr;

// globals.hpp
std::deque<rs *> load_store_buffer;
int PC = 0;
int cycles = 0;
bool stall = false;
bool finished = false;
bool branch_issued = false;
int misprediction_count = 0;
int branch_count = 0;
std::unordered_map<std::string, ushort> inst_op_map({
    {"LOAD", LOAD_OP},
    {"STORE", STORE_OP},
    {"ADDI", ADDI_OP},
    {"ADD", ADD_OP},
    {"DIV", DIV_OP},
    {"BEQ", BEQ_OP},
    {"ABS", ABS_OP},
    {"NEG", NEG_OP},
    {"JAL", JAL_OP},
    {"JALR", JALR_OP},
});
