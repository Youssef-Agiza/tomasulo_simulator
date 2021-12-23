#include "common.hpp"
#include "defs.hpp"
#include "globals.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        emit_error("Usage: <program name> instructions_file.txt data_mem_file.txt");

    read_instructions(argv[1]);
    if (argc > 2)
        read_data_mem(argv[2]);
    initalize_rstable();

    while (!finished)
    {
        cycles++;
        update_stations();
        if (PC < inst_mem.size() && !stall)
        {
#ifdef DEBUGGING

            std::cout << "Trying to issue: ";
            print_inst(inst_mem[PC]);

#endif
            try_issue(inst_mem[PC]);
        }
        update_program_finished();
    }

#ifdef DEBUGGING
    // instruction::print_header();
    // for (auto &inst : inst_mem)
    //     inst.print();
    print_regfile();
    print_data_mem();
#endif
    print_instructions_stats();
    return 0;
}