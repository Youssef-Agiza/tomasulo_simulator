#pragma once
#ifndef DEFS_H
#define DEFS_H
#include "common.hpp"

struct rs;
struct instruction;

// issue.cpp
extern void issue_load(rs *);
extern void issue_store(rs *);
extern void issue_beq(rs *);
extern void issue_jump(rs *);
extern void issue_add_addi(rs *);
extern void issue_jal_jalr(rs *);
extern void issue_div(rs *);
extern void issue_neg(rs *);
extern void issue_abs(rs *);

// exec.cpp
extern bool can_exec_load(rs *);
extern bool can_exec_store(rs *);
extern bool can_exec_beq(rs *);
extern bool can_exec_add_addi(rs *);
extern bool can_exec_div(rs *);
extern bool can_exec_jal_jalr(rs *);
extern bool can_exec_neg(rs *);
extern bool can_exec_abs(rs *);

// wb.cpp
extern void wb_load(rs *);
extern void wb_store(rs *);
extern void wb_beq(rs *);
extern void wb_add_addi(rs *);
extern void wb_div(rs *);
extern void wb_jal_jalr(rs *);
extern void wb_neg(rs *);
extern void wb_abs(rs *);

// rs.cpp
extern void initalize_station_name(std::vector<rs> &stations, const std::string &base_name);
extern void initalize_rstable();

#endif
