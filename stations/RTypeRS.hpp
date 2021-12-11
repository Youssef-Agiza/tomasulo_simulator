#ifndef RTypeRS_H
#define RTypeRS_H
#include "RS.hpp"

// DIV,ADD
struct RTypeRS : public rs
{

    ushort _Vj;
    ushort _Qj;

    ushort _Vk;
    ushort _Qk;
};

#endif