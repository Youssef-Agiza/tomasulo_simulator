#include "common.hpp"
#include "defs.hpp"
#include "globals.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        emit_error("usage: <program name> <instructions file>.txt");

    std::string file_name = argv[1];
    // file_name = "inst.txt";
    fetch_instructions(file_name);
    initalize_rstable();
    while (!finished)
    {
        cycles++;
        update_stations();
        if (PC < inst_mem.size() && !stall)
        {
#ifdef DEBUGGING
            std::cout << "Trying: ";
            inst_mem[PC].print();
#endif
            try_issue(inst_mem[PC]);
        }
        update_finished();
    }

#ifdef DEBUGGING
    instruction::print_header();
    for (auto &inst : inst_mem)
        inst.print();
    print_regfile();
    print_data_mem();
#endif
    // std::cout << regs[2] << "  " << regs[5] << "  " << regs[3] << "\n";

    return 0;
}