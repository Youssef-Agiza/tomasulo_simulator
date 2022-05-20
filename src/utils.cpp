#include "defs.hpp"
#include "instruction.hpp"
#include "globals.hpp"
static const int w = 15;

void get_user_input()
{
    std::string res;
    char answer = 'x';

    std::cout << "Enter starting PC(default=0): ";
    std::getline(std::cin, res);
    if (res[0] != '\n' && res.length())
    {
        if (!isNumber(res))
            std::cout << "Input given is not a number! using PC=0\n";
        else
            PC = std::stoi(res);
    }
    std::cout << "Starting PC from " << PC << "\n";

    std::cout << "would you like to initialize the data memory from a file?(y/n)";
    std::cin >> answer;
    answer = toupper(answer);
    while (answer != 'Y' && answer != 'N')
    {
        std::cout << "Invalid answer!\n";
        std::cout << "would you like to initialize the data memory from a file?(y/n)";
        std::cin >> answer;
        answer = toupper(answer);
    }
    if (answer == 'Y')
    {
        std::cout << "Enter file name: ";
        std::cin >> res;
        read_data_mem(res);
    }
    get_hardware_params();
}

// helper for get_hardware_params
static void get_unit_params(int &num, const std::string &prompt)
{

    std::cout << prompt;
    std::cin >> num;
    while (num <= 0)
    {
        std::cout << "Number must be greater than zero\n";
        std::cout << prompt + ": ";
        std::cin >> num;
    }
}

void get_hardware_params()
{

    char answer = 'x';
    std::cout << "Do you want to customize the hardware?(y/n)";
    std::cin >> answer;
    answer = toupper(answer);
    while (answer != 'Y' && answer != 'N')
    {
        "Enter a valid answer!\n";
        std::cout << "Do you want to customize the hardware?(y/n)";
        std::cin >> answer;
        answer = toupper(answer);
    }

    if (answer == 'Y')
    {

        std::string unit_names[] = {"store", "beq", "abs", "add/i", "jal/r", "div", "neg"};
        int *N[] = {&N_STORE, &N_BEQ, &N_ABS, &N_ADD, &N_JAL, &N_DIV, &N_NEG};
        int *NC_EXEC[] = {&NC_EXEC_STORE, &NC_EXEC_BEQ, &NC_EXEC_ABS, &NC_EXEC_ADD, &NC_EXEC_JAL, &NC_EXEC_DIV, &NC_EXEC_NEG};
        const int size = sizeof(unit_names) / sizeof(unit_names[0]);

        // prompt msgs
        std::string base_prompt = "Enter number of ";
        std::string n_stations_prompt = base_prompt + "reservation stations for ";
        std::string nc_exec_prompt = base_prompt + "execution cycles for ";

        get_unit_params(N_LOAD, n_stations_prompt + "load");
        get_unit_params(NC_EXEC_ADDRESS_LOAD, base_prompt + "computing address for load");
        get_unit_params(NC_EXEC_MEM_LOAD, base_prompt + "reading from memory for load");
        for (int i = 0; i < size; i++)
        {
            get_unit_params(*N[i], n_stations_prompt + unit_names[i] + ": ");
            get_unit_params(*NC_EXEC[i], nc_exec_prompt + unit_names[i] + ": ");
        }
        get_unit_params(NC_WB_REGFILE, base_prompt + "cycles writing to regfile: ");
        get_unit_params(NC_WB_MEM, base_prompt + "cycles for writing to memory: ");
    }
}

void print_inst_header(std::ostream &outs)
{
    using std::setw;
    outs << setw(w) << "name";
#ifdef DEBUGGING
    outs << setw(w) << "rd" << setw(w) << "rs1" << setw(w) << "rs2" << setw(w) << "imm";
#endif

    outs << setw(w) << "PC" << setw(w) << "issue" << setw(w) << "exec start" << setw(w) << "exec finish" << setw(w) << "wb"
         << "\n";
}
void print_inst(const instruction &inst, std::ostream &outs)
{
    using std::setw;
    outs << setw(w) << inst.name;
#ifdef DEBUGGING
    outs << setw(w) << (signed short)inst.rd << setw(w) << (signed short)inst.rs1 << setw(w) << (signed short)inst.rs2 << setw(w) << inst.imm;
#endif
    outs << setw(w) << inst.pc << setw(w) << inst.issue_cycle << setw(w) << inst.exec_start_cycle << setw(w) << inst.exec_finish_cycle << setw(w) << inst.wb_cycle << "\n";
}

void print_instructions_stats(std::ostream &outs)
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
        // outs << std::setfill('-') << std::setw(50) << "No Instructions were executed" << std::setw(50) << std::setfill('-') << "\n";
        outs << std::setw(50) << "No Instructions were executed" << std::setw(50) << "\n";
    }
    else
    {

        outs << "\n"
             << std::setw(70) << "Printing Instructions Stats" << std::setw(50) << "\n\n";
        // outs << std::setw(50) << std::setfill('-') << "Printing Instructions Stats" << std::setw(50) << std::setfill('-') << "\n";
        print_inst_header(outs);
        for (const auto &inst : inst_mem)
            if (inst.executed)
            {
                print_inst(inst, outs);
                IPC++;
            }
    }
    IPC = (cycles > 0) ? ((float)IPC) / cycles : 0;
    float mispredictin_percentage = (branch_count > 0) ? ((float)misprediction_count) / ((float)(branch_count)) * 100 : 0;

    outs << "\n\nTotal cycles spanned: " << cycles << "\n";
    outs << "IPC: " << IPC << "\n";
    outs << "Branch misprediction: " << mispredictin_percentage << "%\n";
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
void print_regfile(std::ostream &outs)
{
    outs << "\n"
         << std::setw(50) << "REGFILE" << std::setw(50) << "\n";
    // outs << "\n" << std::setfill('-') << std::setw(50) << "REGFILE" << std::setw(50) << "\n";
    for (int i = 0; i < REGFILE_SIZE; i++)
        outs << std::setw(35) << "x" << i << "=" << ((signed short)regs[i]) << "\n";
}
void print_data_mem(std::ostream &outs)
{
    outs << "\n"
         << std::setw(50) << "DATA MEMORY" << std::setw(50) << "\n\n";
    // outs << "\n"<< std::setfill('-') << std::setw(50) << "DATA MEMORY" << std::setw(50) << "\n";
    for (int i = 0; i < MEMORY_SIZE; i += 8)
    {
        for (int j = 0; j < 8 && j + i < MEMORY_SIZE; j++)
            outs << std::setw(10) << i + j << " -- " << (signed int)data_mem[i + j] << std::setw(10);
        outs << "\n";
    }
}

// func: function pointer, params: parameters passed to func
// output: iterates on all units and executes the func.
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
