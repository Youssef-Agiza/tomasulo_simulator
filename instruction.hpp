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

    instruction()
    {
        name = "";
        rd = -1;
        rs1 = -1;
        rs2 = -1;
        imm = 0;
        address = 0;
    }
    static void print_header()
    {
        using std::setw;
        static const int w = 10;
        std::cout << setw(w) << "name" << setw(w) << "rd" << setw(w) << "rs1" << setw(w) << "rs2" << setw(w) << "imm"
                  << "\n";
    }
    void print()
    {
        using std::setw;
        static const int w = 10;
        std::cout << setw(w) << name << setw(w) << rd << setw(w) << rs1 << setw(w) << rs2 << setw(w) << imm << "\n";
    }
};

#endif