#ifndef ITypeRS_H
#define ITypeRS_H
#include "RS.hpp"

struct ITypeRS : public RS
{
    uint _imm;
    ushort _Vj;
    ushort _Qj;
};

#endif