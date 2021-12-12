#include "common.hpp"
#include "mem.hpp"
#include "regs.hpp"
#include "rs.hpp"
#include "instruction.hpp"
#include "defs.hpp"
#include "cdb.hpp"
#include "globals.hpp"

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
    if (name == "NEG" || name == "ABS" || name == "JALR")
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
	if (name == "LOAD")
    {
        ss >> rd >> imm >> rs1;
        inst.rd = decode_reg(rd);
        inst.imm = std::stoi(imm);
		inst.rs1 = decode_reg(rs1);
    }
	if (name == "JAL")
    {
        ss >> rd >> imm;
        inst.rd = decode_reg(rd);
        inst.imm = std::stoi(imm);
    }
	if (name == "STORE")
    {
        ss >> rs2 >> imm >> rs1;
        inst.rs2 = decode_reg(rs2);
        inst.imm = std::stoi(imm);
		inst.rs1 = decode_reg(rs1);
    }
	if (name == "BEQ")
    {
        ss >> rs1 >> rs2 >> imm;
        inst.rs2 = decode_reg(rs2);
        inst.imm = std::stoi(imm);
		inst.rs1 = decode_reg(rs1);
    }
    inst.print();
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

void update_stations()
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

void broadcast_station(CDB &c, rs &st)
{
    if (c.st == st.Qk_)
    {
        st.Qk_ = nullptr;
        st.Vk_ = c.rd;
    }
    else if (c.st == st.Qj_)
    {
        st.Qj_ = nullptr;
        st.Vj_ = c.rd;
    }
}

void broadcast()
{
    if (cdb.empty())
        return;

    // for (auto c : cdb)
    // {
    //     for (auto &st : rstable.load)
    //         broadcast_station(c, st);

    //     for (auto &st : rstable.store)
    //         broadcast_station(c, st);

    //     for (auto &st : rstable.add_addi)
    //         broadcast_station(c, st);

    //     for (auto &st : rstable.abs)
    //         broadcast_station(c, st);

    //     for (auto &st : rstable.beq)
    //         broadcast_station(c, st);

    //     for (auto &st : rstable.div)
    //         broadcast_station(c, st);

    //     for (auto &st : rstable.jal_jalr)
    //         broadcast_station(c, st);

    //     for (auto &st : rstable.neg)
    //         broadcast_station(c, st);
    // }
    // cdb.pop_back();
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
        update_stations();
        if (PC < inst_mem.size()&&!stall)
            try_issue(inst_mem[PC]);
    }
    std::cout << regs[2] << "  " << regs[5] << "  " << regs[3] << "\n";

    return 0;
}