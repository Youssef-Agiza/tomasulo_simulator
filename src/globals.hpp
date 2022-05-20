#ifndef GLOBALS_H
#define GLOBALS_H
#include "common.hpp"

#include "rs.hpp"
#include "mem.hpp"
#include "regs.hpp"
#include "cdb.hpp"

// map from instruction name to op code
extern std::unordered_map<std::string, ushort> inst_op_map;

extern std::deque<rs *> load_store_buffer;
extern int PC;
extern int cycles;
extern bool stall;
extern bool finished;
extern bool branch_issued;
extern int misprediction_count;
extern int branch_count;

#endif
