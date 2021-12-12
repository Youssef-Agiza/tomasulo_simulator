#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "common.hpp"

struct instruction
{
    std::string name;
    ushort rd;
    ushort rs1;
    ushort rs2;
    uint imm;
    uint pc;
    int issue_cycle;
    int exec_start_cycle;
    int exec_finish_cycle;
    int wb_cycle;

    instruction()
    {
        name = "";
        rd = -1;
        rs1 = -1;
        rs2 = -1;
        imm = 0;
        pc = -1;
        exec_start_cycle = -1;
        issue_cycle = -1;
        exec_finish_cycle = -1;
        wb_cycle = -1;
    }
    static void print_header()
    {
        using std::setw;
        static const int w = 10;
        std::cout << setw(w) << "name" << setw(w) << "rd" << setw(w) << "rs1" << setw(w) << "rs2" << setw(w) << "imm"
                  << setw(w) << "issue" << setw(w) << "exec1" << setw(w) << "exec2" << setw(w) << "wb"
                  << "\n";
    }
    void print()
    {
        using std::setw;
        static const int w = 10;
        std::cout << setw(w) << name << setw(w) << rd << setw(w) << rs1 << setw(w) << rs2 << setw(w) << imm
                  << setw(w) << issue_cycle << setw(w) << exec_start_cycle << setw(w) << exec_finish_cycle << setw(w) << wb_cycle << "\n";
    }
};

#endif