#ifndef GLOBALS_H
#define GLOBALS_H
#include "common.hpp"

#include "rs.hpp"
#include "mem.hpp"
#include "regs.hpp"
#include "cdb.hpp"

// number of stations for each unit
// rs.cpp
extern int N_LOAD;
extern int N_STORE;
extern int N_BEQ;
extern int N_JAL;
extern int N_ADD;
extern int N_NEG;
extern int N_ABS;
extern int N_DIV;

// number of execution cycles for each station
// exec.cpp
extern int NC_EXEC_ADDRESS_LOAD;
extern int NC_EXEC_MEM_LOAD;
extern int NC_EXEC_STORE;
extern int NC_EXEC_BEQ;
extern int NC_EXEC_JAL;
extern int NC_EXEC_ADD;
extern int NC_EXEC_NEG;
extern int NC_EXEC_ABS;
extern int NC_EXEC_DIV;

// number of write back cycles for each station
// wb.cpp

extern int NC_WB_REGFILE;
extern int NC_WB_MEM;
// extern int NC_WB_LOAD;
// extern int NC_WB_STORE;
// extern int NC_WB_BEQ;
// extern int NC_WB_JAL;
// extern int NC_WB_ADD;
// extern int NC_WB_NEG;
// extern int NC_WB_ABS;
// extern int NC_WB_DIV;

// map from instruction name to op code
extern std::unordered_map<std::string, ushort> inst_op_map;

extern std::deque<rs *> load_store_buffer;
extern int PC;
extern int cycles;
extern bool stall;
extern bool finished;
extern bool branch_issued;

#endif
