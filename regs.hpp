#ifndef REGFILE_H
#define REGFILE_H
#include "common.hpp"
struct rs;

#define REG_SIZE 16
#define REGFILE_SIZE 8

extern ushort regs[REGFILE_SIZE];

struct RegStat
{
    rs *Qi;
};
extern struct RegStat regstat[REGFILE_SIZE];

#endif