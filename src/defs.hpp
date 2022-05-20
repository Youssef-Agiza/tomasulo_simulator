#pragma once
#ifndef DEFS_H
#define DEFS_H
#include "common.hpp"

struct rs;
struct instruction;

// rs.cpp
extern void initalize_rstable();

// files.cpp
extern void read_instructions(const std::string &file_name);
extern void read_data_mem(const std::string &file_name);
extern short decode_reg(const std::string &reg_str);
extern void decode_line(const std::string &line, instruction &inst);
extern void output_to_file(const std::string &filename);

// utils.cpp
extern void emit_error(const std::string &err);
extern void toupper(std::string &str);
extern bool isNumber(const std::string &str);
extern void get_user_input();
extern void get_hardware_params();
extern void print_data_mem(std::ostream &outs = std::cout);
extern void print_regfile(std::ostream &outs = std::cout);
extern void print_inst_header(std::ostream &outs = std::cout);
extern void print_inst(const instruction &inst, std::ostream &outs = std::cout);
extern void print_instructions_stats(std::ostream &outs = std::cout);
extern void iterate_on_stations(void (*func)(rs &st, void *p), void *params = nullptr);

// update.cpp
extern void update_stations();
extern void update_program_finished();
extern void broadcast();
extern void flush_stations(uint start_pc);
extern void save_regstate();

// issue.cpp
extern void try_issue(instruction &inst);
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
extern void exec_load(rs *);
extern void exec_store(rs *);
extern void exec_beq(rs *);
extern void exec_add_addi(rs *);
extern void exec_div(rs *);
extern void exec_jal_jalr(rs *);
extern void exec_neg(rs *);
extern void exec_abs(rs *);

// can_exec.cpp
extern bool can_exec_load(rs *);
extern bool can_exec_store(rs *);
extern bool can_exec_beq(rs *);
extern bool can_exec_add_addi(rs *);
extern bool can_exec_div(rs *);
extern bool can_exec_jal_jalr(rs *);
extern bool can_exec_neg(rs *);
extern bool can_exec_abs(rs *);

// wb.cpp
extern void wb_mem(rs *);
extern void wb_regfile(rs *);
extern void wb_beq(rs *);
extern void wb_jal_jalr(rs *);

#endif
