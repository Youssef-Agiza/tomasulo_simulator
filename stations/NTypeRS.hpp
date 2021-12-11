#ifndef NTYPE_RS_H
#define NTYPE_RS_H
#include "RS.hpp"

// NEG,ABS,JALR
class NTypeRS : public rs
{
    ushort Vj_;
    ushort Qj_;
};
#endif