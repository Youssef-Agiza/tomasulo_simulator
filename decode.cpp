#include "defs.hpp"
#include "common.hpp"
#include "instruction.hpp"
#include "globals.hpp"

void fetch_instructions(const std::string &file_name)
{
    std::ifstream inf(file_name);
    if (inf.fail())
        emit_error("Couldn't open file");

    std::string line;

    while (std::getline(inf, line))
    {
        instruction new_inst;
        decode_line(line, new_inst);
        inst_mem.push_back(new_inst);
    }

    inf.close();
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
    inst.rs1 = -1;
    inst.rs2 = -1;
    inst.rd = -1;

    std::string name, rs1, rs2, rd, imm;
    ss >> name;

    toupper(name);
    if (inst_op_map.find(name) == inst_op_map.end())
        emit_error("Unknown instruction: " + name + "\n");

    inst.name = name;
    inst.op = inst_op_map[name];
    inst.pc = PC;

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
#ifdef DEBUGGING
    // inst.print();
#endif
}