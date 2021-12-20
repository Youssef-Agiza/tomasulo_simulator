#pragma once
#ifndef PARAMS_H
#define PARAMS_H

// #define DEBUGGING

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

// number of units
#define DEFAULT_N_LOAD 2
#define DEFAULT_N_STORE 2
#define DEFAULT_N_BEQ 1
#define DEFAULT_N_JAL 1
#define DEFAULT_N_ADD 3
#define DEFAULT_N_NEG 1
#define DEFAULT_N_ABS 1
#define DEFAULT_N_DIV 1

// number of cycles for each station
#define DEFAULT_NC_EXEC_ADDRESS_LOAD 2
#define DEFAULT_NC_EXEC_MEM_LOAD 2
#define DEFAULT_NC_EXEC_STORE 2
#define DEFAULT_NC_EXEC_BEQ 1
#define DEFAULT_NC_EXEC_JAL 1
#define DEFAULT_NC_EXEC_ADD 2
#define DEFAULT_NC_EXEC_NEG 3
#define DEFAULT_NC_EXEC_ABS 2
#define DEFAULT_NC_EXEC_DIV 10

// number of write back cycles for regfile and memory
#define DEFAULT_NC_WB_REGFILE 1
#define DEFAULT_NC_WB_MEM 2

// #define DEFAULT_NC_WB_LOAD 2
// #define DEFAULT_NC_WB_STORE 2
// #define DEFAULT_NC_WB_BEQ 1
// #define DEFAULT_NC_WB_JAL 1
// #define DEFAULT_NC_WB_ADD 1
// #define DEFAULT_NC_WB_NEG 1
// #define DEFAULT_NC_WB_ABS 1
// #define DEFAULT_NC_WB_DIV 1

#endif