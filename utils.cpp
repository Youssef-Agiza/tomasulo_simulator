#include "defs.hpp"
#include "instruction.hpp"
#include "globals.hpp"

void emit_error(const std::string &err)
{
    std::cerr << "Error: " << err;
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
              << std::setfill('-') << std::setw(50) << "REFILE" << std::setw(50) << "\n";
    for (int i = 0; i < REGFILE_SIZE; i++)
        std::cout << "x" << i << "=" << regs[i] << "\n";
}
void print_data_mem()
{
    std::cout << "\n"
              << std::setfill('-') << std::setw(50) << "DATA MEMORY" << std::setw(50) << "\n";
    for (int i = 0; i < 20; i++)
        std::cout << i << " -- " << data_mem[i] << "\n";
}
void try_issue(instruction &inst)
{
    if (inst.name == "LOAD")
        for (auto &st : rstable.load)
            if (st.state_ == IDLE)
            {
                load_store_buffer.push_back(&st);
                st.issue(inst);
                PC++;
                return;
            }

    if (inst.name == "STORE")
        for (auto &st : rstable.store)
            if (st.state_ == IDLE)
            {
                load_store_buffer.push_back(&st);
                st.issue(inst);
                PC++;
                return;
            }

    if (inst.name == "BEQ")
        for (auto &st : rstable.beq)
            if (st.state_ == IDLE)
            {
                st.issue(inst);
                PC++;
                issued_branch = true;
                return;
            }

    if (inst.name == "JAL" || inst.name == "JALR")
        for (auto &st : rstable.jal_jalr)
            if (st.state_ == IDLE)
            {
                inst.pc = PC;
                st.issue(inst);
                stall = true;
                return;
            }

    if (inst.name == "NEG")
        for (auto &st : rstable.neg)
            if (st.state_ == IDLE)
            {
                st.issue(inst);
                PC++;
                return;
            }

    if (inst.name == "DIV")
        for (auto &st : rstable.div)
            if (st.state_ == IDLE)
            {
                st.issue(inst);
                PC++;
                return;
            }

    if (inst.name == "ABS")
        for (auto &st : rstable.abs)
            if (st.state_ == IDLE)
            {
                st.issue(inst);
                PC++;
                return;
            }

    if (inst.name == "ADD" || inst.name == "ADDI")
        for (auto &st : rstable.add_addi)
            if (st.state_ == IDLE)
            {
                st.issue(inst);
                PC++;
                return;
            }
}
