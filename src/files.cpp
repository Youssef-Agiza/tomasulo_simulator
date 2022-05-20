#include "defs.hpp"
#include "common.hpp"
#include "instruction.hpp"
#include "globals.hpp"

void read_data_mem(const std::string &file_name)
{
    std::ifstream inf(file_name);
    if (inf.fail())
        emit_error("Error: Couldn't open data memory file");

    std::string line, addr, val;
    std::cout << std::setw(20) << std::setw(20) << "READING DATA MEMORY FROM " << file_name << "...." << std::setw(20) << "\n";

    while (std::getline(inf, line))
    {
        std::stringstream ss(line);
        ss >> addr >> val;
        if (!isNumber(addr) || !isNumber(val))
            emit_error("Error: data memory can only contain numbers");

        data_mem[std::stoi(addr) % MEMORY_SIZE] = std::stoi(val);
#ifdef DEBUGGING
        std::cout << "Reading " << val << " to address " << addr << "...\n";
#endif
    }

    inf.close();
}
void read_instructions(const std::string &file_name)
{
    std::ifstream inf(file_name);
    if (inf.fail())
        emit_error("Error: Couldn't open instructions file");

    std::string line;
    int pc = 0;
    while (std::getline(inf, line))
    {
        if (line.empty())
            continue;

        instruction new_inst;
        new_inst.pc = pc++;
        decode_line(line, new_inst);
        inst_mem.push_back(new_inst);
    }

    inf.close();
}

short decode_reg(const std::string &reg_str)
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

    if (inst.op == ADD_OP || inst.op == DIV_OP)
    {
        ss >> rd >> rs1 >> rs2;
        inst.rd = decode_reg(rd);
        inst.rs1 = decode_reg(rs1);
        inst.rs2 = decode_reg(rs2);
    }
    if (inst.op == NEG_OP || inst.op == ABS_OP || inst.op == JALR_OP)
    {
        ss >> rd >> rs1;
        inst.rd = decode_reg(rd);
        inst.rs1 = decode_reg(rs1);
    }
    if (inst.op == ADDI_OP || inst.op == LOAD_OP)
    {
        ss >> rd >> rs1 >> imm;
        inst.rd = decode_reg(rd);
        inst.rs1 = decode_reg(rs1);
        inst.imm = std::stoi(imm);
    }
    if (inst.op == JAL_OP)
    {
        ss >> rd >> imm;
        inst.rd = decode_reg(rd);
        inst.imm = std::stoi(imm);
    }
    if (inst.op == STORE_OP)
    {
        ss >> rs2 >> rs1 >> imm;
        inst.rs2 = decode_reg(rs2);
        inst.imm = std::stoi(imm);
        inst.rs1 = decode_reg(rs1);
    }
    if (inst.op == BEQ_OP)
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

void output_to_file(const std::string &filename)
{
    // char answer;
    // std::cout << "Would you like to save the results to a file?(y/n)";
    // std::cin >> answer;
    // answer = toupper(answer);
    // while (answer != 'Y' && answer != 'N')
    // {
    //     std::cout << "Would you like to save the results to a file?(y/n)";
    //     std::cin >> answer;
    //     answer = toupper(answer);
    // }
    // if (answer == 'N')
    //     return;
    //     if(filen)
    // std::string fname;
    // std::cout << "Enter file name: ";
    // std::cin >> fname;
    std::ofstream outf(filename);
    if (outf.fail())
        emit_error("Error opening output file.");

    print_regfile(outf);
    print_data_mem(outf);
    print_instructions_stats(outf);
}
