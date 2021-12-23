#include "defs.hpp"
#include "instruction.hpp"
#include "globals.hpp"
static const int w = 15;
void print_inst_header()
{
    using std::setw;
    std::cout << setw(w) << "name";
#ifdef DEBUGGING
    std::cout << setw(w) << "rd" << setw(w) << "rs1" << setw(w) << "rs2" << setw(w) << "imm";
#endif

    std::cout << setw(w) << "issue" << setw(w) << "exec start" << setw(w) << "exec finish" << setw(w) << "wb"
              << "\n";
}
void print_inst(const instruction &inst)
{
    using std::setw;
    std::cout << setw(w) << inst.name;
#ifdef DEBUGGING
    std::cout << setw(w) << (signed short)inst.rd << setw(w) << (signed short)inst.rs1 << setw(w) << (signed short)inst.rs2 << setw(w) << inst.imm;
#endif
    std::cout << setw(w) << inst.issue_cycle << setw(w) << inst.exec_start_cycle << setw(w) << inst.exec_finish_cycle << setw(w) << inst.wb_cycle << "\n";
}

void print_instructions_stats()
{
    bool found = false;
    float IPC = 0;
    for (const auto &inst : inst_mem)
        if (inst.executed)
        {
            found = true;
            break;
        }
    if (!found)
    {
        // std::cout << std::setfill('-') << std::setw(50) << "No Instructions were executed" << std::setw(50) << std::setfill('-') << "\n";
        std::cout << std::setw(50) << "No Instructions were executed" << std::setw(50) << "\n";
    }
    else
    {

        std::cout << "\n"
                  << std::setw(50) << "Printing Instructions Stats" << std::setw(50) << "\n";
        // std::cout << std::setw(50) << std::setfill('-') << "Printing Instructions Stats" << std::setw(50) << std::setfill('-') << "\n";
        print_inst_header();
        for (const auto &inst : inst_mem)
            if (inst.executed)
            {
                print_inst(inst);
                IPC++;
            }
    }
    IPC = (cycles > 0) ? ((float)IPC) / cycles : 0;
    float mispredictin_percentage = (branch_count > 0) ? ((float)misprediction_count) / ((float)(branch_count)) * 100 : 0;

    std::cout << "\n\nTotal cycles spanned: " << cycles << "\n";
    std::cout << "IPC: " << IPC << "\n";
    std::cout << "Branch misprediction: " << mispredictin_percentage << "%\n";
}

void emit_error(const std::string &err)
{
    std::cerr << err << "\n";
    exit(-1);
}
void toupper(std::string &str)
{
    for (auto &c : str)
        c = std::toupper(c);
}
bool isNumber(const std::string &str)
{
    for (auto c : str)
        if (!std::isdigit(c))
            return false;
    return true;
}
void print_regfile()
{
    std::cout << "\n"
              << std::setw(50) << "REGFILE" << std::setw(50) << "\n";
    // std::cout << "\n" << std::setfill('-') << std::setw(50) << "REGFILE" << std::setw(50) << "\n";
    for (int i = 0; i < REGFILE_SIZE; i++)
        std::cout << "x" << i << "=" << ((signed short)regs[i]) << "\n";
}
void print_data_mem()
{
    std::cout << "\n"
              << std::setw(50) << "DATA MEMORY" << std::setw(50) << "\n";
    // std::cout << "\n"<< std::setfill('-') << std::setw(50) << "DATA MEMORY" << std::setw(50) << "\n";
    for (int i = 0; i < 20; i++)
        std::cout << i << " -- " << (signed int)data_mem[i] << "\n";
}

void iterate_on_stations(void (*func)(rs &st, void *p), void *params)
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
