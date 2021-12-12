#ifndef GLOBALS_H
#define GLOBALS_H
#include "common.hpp"

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