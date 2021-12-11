#ifndef RS_H
#define RS_H
#include "common.hpp"

struct rs // base reservation station
{
    int cycle_count_;
    std::string name_;
    bool busy_;
    ushort op_;
    ushort rd_;

    ushort Vj_;
    ushort Qj_;

    ushort Vk_;
    ushort Qk_;

    ushort A_;
};

#endif