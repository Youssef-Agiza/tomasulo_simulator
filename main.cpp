#include "common.hpp"
#include "defs.hpp"
#include "globals.hpp"

int main()
{

    std::string file_name = "inst.txt";
    fetch_instructions(file_name);
    initalize_rstable();

    while (!finished)
    {
        cycles++;
        std::cout << "Cycle: " << cycles << "\n";
        update_stations();
        if (PC < inst_mem.size() && !stall)
            try_issue(inst_mem[PC]);

        update_finished();
    }

#ifdef DEBUGGING
    instruction::print_header();
    for (auto &inst : inst_mem)
        inst.print();
    print_regfile();
#endif
    // std::cout << regs[2] << "  " << regs[5] << "  " << regs[3] << "\n";

    return 0;
}