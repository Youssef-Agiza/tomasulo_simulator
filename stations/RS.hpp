#ifndef RS_H
#define RS_H
#include "common.hpp"

struct RS // base reservation station
{
    std::string _name;
    bool _busy;
    ushort _op;

    ushort _Vj;
    ushort _Qj;

    ushort _Vk;
    ushort _Qk;

    ushort _Addres;
};

#endif