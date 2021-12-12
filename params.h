#pragma once
#ifndef PARAMS_H
#define PARAMS_H

#define DEBUGGING

#define ADD_OP 0x0
#define ADDI_OP 0x1
#define JAL_OP 0x2
#define JALR_OP 0x3

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
#define DEFAULT_NC_EXEC_LOAD 4
#define DEFAULT_NC_EXEC_STORE 2
#define DEFAULT_NC_EXEC_BEQ 1
#define DEFAULT_NC_EXEC_JAL 1
#define DEFAULT_NC_EXEC_ADD 2
#define DEFAULT_NC_EXEC_NEG 3
#define DEFAULT_NC_EXEC_ABS 2
#define DEFAULT_NC_EXEC_DIV 10

// number of write back cycles for each station
#define DEFAULT_NC_WB_LOAD 2
#define DEFAULT_NC_WB_STORE 2
#define DEFAULT_NC_WB_BEQ 1
#define DEFAULT_NC_WB_JAL 1
#define DEFAULT_NC_WB_ADD 1
#define DEFAULT_NC_WB_NEG 1
#define DEFAULT_NC_WB_ABS 1
#define DEFAULT_NC_WB_DIV 1

#endif