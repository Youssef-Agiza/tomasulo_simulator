#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "common.hpp"

#define NO_OP 0x0
#define ADD_OP 0x1
#define ADDI_OP 0x2
#define JAL_OP 0x3
#define JALR_OP 0x4
#define LOAD_OP 0x5
#define STORE_OP 0x6
#define BEQ_OP 0x7
#define DIV_OP 0x8
#define NEG_OP 0x9
#define ABS_OP 0xA

struct instruction
{
    std::string name;
    ushort op;
    short rd;
    short rs1;
    short rs2;
    int imm;
    int pc;
    bool executed;
    int issue_cycle;
    int exec_start_cycle;
    int exec_finish_cycle;
    int wb_cycle;

    instruction()
    {
        reset();
    }
    void reset()
    {
        name = "";
        op = NO_OP;
        executed = false;
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
};

#endif