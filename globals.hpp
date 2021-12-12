#ifndef GLOBALS_H
#define GLOBALS_H
#include "common.hpp"
<<<<<<< HEAD

#include "rs.hpp"
#include "mem.hpp"
#include "regs.hpp"
#include "cdb.hpp"

extern int PC;
extern int cycles;
extern bool stall;
extern bool finished;
extern bool issued_branch;

#endif
=======
#include "instruction.hpp"
#include "cdb.hpp"

extern std::vector<instruction> inst_mem; 
extern std::deque<struct CDB> cdb;
 
extern int PC ;
extern int cycles; 
extern bool stall;
#endif 
>>>>>>> 36bc7d1f224494750c3028f84d6935611f593660
