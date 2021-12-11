#include "common.hpp"
#include "mem.hpp"
#include "regs.hpp"
#include "rs.hpp"
#include "instruction.hpp"
#include "defs.hpp"
ushort regs[REGFILE_SIZE];
uint mem[MEMORY_SIZE];
std::vector<instruction> inst_mem;
struct RegStat regstat[REGFILE_SIZE];

int PC = 0;
int cycles = 0;

void emit_error(const std::string &err)
{
    std::cout << "Error: " << err;
    exit(-1);
}
void toupper(std::string &str)
{
    for (auto &c : str)
        c = std::toupper(c);
}
ushort decode_reg(const std::string &reg_str)
{
    try
    {
        return std::stoi(reg_str.substr(1));
    }
    catch (std::invalid_argument e)
    {
        emit_error(e.what());
    }
    return -1;
}
void decode_line(const std::string &line, instruction &inst)
{
    std::stringstream ss(line);
    // std::cout << "inst" << cycles++ << ": ";
    std::string name, rs1, rs2, rd, imm;
    ss >> name;

    toupper(name);
    inst.name = name;
    if (name == "ADD" || name == "DIV")
    {
        ss >> rd >> rs1 >> rs2;
        inst.rd = decode_reg(rd);
        inst.rs1 = decode_reg(rs1);
        inst.rs2 = decode_reg(rs2);
    }
    if (name == "NEG" || name == "ABS")
    {
        ss >> rd >> rs1;
        inst.rd = decode_reg(rd);
        inst.rs1 = decode_reg(rs1);
    }
    if (name == "ADDI")
    {
        ss >> rd >> rs1 >> imm;
        inst.rd = decode_reg(rd);
        inst.rs1 = decode_reg(rs1);
        inst.imm = std::stoi(imm);
    }
}

void try_issue(instruction &inst)
{
    if (inst.name == "ADD" || inst.name == "ADDI")
        for (auto &st : rstable.add_addi)
            if (st.state_ == IDLE)
            {
                st.inst_ = &inst;
                st.issue_(&st);
                PC++;
                break;
            }
}

void fetch_instructions(const std::string &file_name)
{
    std::ifstream inf(file_name);
    if (inf.fail())
        emit_error("Couldn't open file");

    std::string line, inst;
    while (std::getline(inf, line))
    {
        instruction new_inst;
        decode_line(line, new_inst);
        inst_mem.push_back(new_inst);
    }

    inf.close();
}

void execute_stations()
{

    // for (auto &st : rstable.load)
    //     st.update();

    // for (auto &st : rstable.store)
    //     st.update();

    for (auto &st : rstable.add_addi)
        st.update();

    // for (auto &st : rstable.abs)
    //     st.update();

    // for (auto &st : rstable.beq)
    //     st.update();

    // for (auto &st : rstable.div)
    //     st.update();

    // for (auto &st : rstable.jal_jalr)
    //     st.update();

    // for (auto &st : rstable.neg)
    //     st.update();
}

bool finished()
{

    if (PC < inst_mem.size())
        return false;

    for (const auto &st : rstable.load)
        if (st.state_ != IDLE)
            return false;

    for (auto &st : rstable.store)
        if (st.state_ != IDLE)
            return false;

    for (auto &st : rstable.add_addi)
        if (st.state_ != IDLE)
            return false;

    for (auto &st : rstable.abs)
        if (st.state_ != IDLE)
            return false;

    for (auto &st : rstable.beq)
        if (st.state_ != IDLE)
            return false;

    for (auto &st : rstable.div)
        if (st.state_ != IDLE)
            return false;

    for (auto &st : rstable.jal_jalr)
        if (st.state_ != IDLE)
            return false;

    for (auto &st : rstable.neg)
        if (st.state_ != IDLE)
            return false;

    return true;
}

int main()
{

    std::string file_name = "inst.txt";
    fetch_instructions(file_name);
    initalize_rstable();

    while (!finished())
    {
        cycles++;
        execute_stations();
        if (PC < inst_mem.size())
            try_issue(inst_mem[PC]);
    }
    std::cout << regs[2] << "  " << regs[5] << "  " << regs[3] << "\n";

    return 0;
}