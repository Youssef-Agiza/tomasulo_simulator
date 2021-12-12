#ifndef GLOBALS_H
#define GLOBALS_H
#include "common.hpp"
#include "instruction.hpp"
#include "cdb.hpp"

extern std::vector<instruction> inst_mem; 
extern std::deque<struct CDB> cdb;
 
extern int PC ;
extern int cycles; 
extern bool stall;
#endif 