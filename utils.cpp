#include "defs.hpp"
#include "instruction.hpp"
#include "globals.hpp"

void emit_error(const std::string &err)
{
    std::cerr << "\nError: " << err << "\n";
    exit(-1);
}
void toupper(std::string &str)
{
    for (auto &c : str)
        c = std::toupper(c);
}
void print_regfile()
{
    std::cout << "\n"
              << std::setfill('-') << std::setw(50) << "REGFILE" << std::setw(50) << "\n";
    for (int i = 0; i < REGFILE_SIZE; i++)
        std::cout << "x" << i << "=" << ((signed short)regs[i]) << "\n";
}
void print_data_mem()
{
    std::cout << "\n"
              << std::setfill('-') << std::setw(50) << "DATA MEMORY" << std::setw(50) << "\n";
    for (int i = 0; i < 20; i++)
        std::cout << i << " -- " << (signed int)data_mem[i] << "\n";
}

extern void iterate_on_stations(void (*func)(rs &st, void *p), void *params)
{

    for (auto &st : rstable.load)
        func(st, params);

    for (auto &st : rstable.store)
        func(st, params);

    for (auto &st : rstable.add_addi)
        func(st, params);

    for (auto &st : rstable.abs)
        func(st, params);

    for (auto &st : rstable.beq)
        func(st, params);

    for (auto &st : rstable.div)
        func(st, params);

    for (auto &st : rstable.jal_jalr)
        func(st, params);

    for (auto &st : rstable.neg)
        func(st, params);
}
