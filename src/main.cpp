#include "common.hpp"
#include "defs.hpp"
#include "globals.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        emit_error("Usage: <program name> instructions_file <optional:output_file>");

    read_instructions(argv[1]);
    get_user_input();
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

    // #ifdef DEBUGGING
    // instruction::print_header();
    // for (auto &inst : inst_mem)
    //     inst.print();
    // #endif
    print_regfile();
    print_data_mem();
    print_instructions_stats();

    if (argc > 2)
        output_to_file(argv[2]);
    return 0;
}