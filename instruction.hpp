#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "common.hpp"

struct instruction
{
    uint address; // keep track of instruction address
    std::string name;
    ushort rd;
    ushort rs1;
    ushort rs2;
    uint imm;
    void print()
    {
        using std::setw;
        std::cout << setw(10) << name << setw(10) << rd << setw(10) << rs1 << setw(10) << rs2 << setw(10) << imm << "\n";
    }
};

#endif