#pragma once
#ifndef PARAMS_H
#define PARAMS_H

#define DEBUGGING
#define EXTRA_INFO

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

// number of stations for each unit
// rs.cpp
extern int N_LOAD;
extern int N_STORE;
extern int N_BEQ;
extern int N_JAL;
extern int N_ADD;
extern int N_NEG;
extern int N_ABS;
extern int N_DIV;

// number of execution cycles for each station
// exec.cpp
extern int NC_EXEC_ADDRESS_LOAD;
extern int NC_EXEC_MEM_LOAD;
extern int NC_EXEC_STORE;
extern int NC_EXEC_BEQ;
extern int NC_EXEC_JAL;
extern int NC_EXEC_ADD;
extern int NC_EXEC_NEG;
extern int NC_EXEC_ABS;
extern int NC_EXEC_DIV;

// number of write back cycles for each station
// wb.cpp

extern int NC_WB_REGFILE;
extern int NC_WB_MEM;

#endif