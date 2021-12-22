#include "defs.hpp"
#include "rs.hpp"
#include "regs.hpp"

int NC_WB_REGFILE = DEFAULT_NC_WB_REGFILE;
int NC_WB_MEM = DEFAULT_NC_WB_MEM;

static void save_wb_cycle(rs *RS)
{
    RS->inst_->wb_cycle = RS->cycles_counter_ + RS->inst_->exec_finish_cycle;
    RS->state_ = FINISHED;
}

void wb_mem(rs *RS)
{
    ++RS->cycles_counter_;
    if (RS->Qk_ != nullptr || RS->cycles_counter_ < NC_WB_MEM)
        return;

    data_mem[RS->imm_ % MEMORY_SIZE] = RS->Vk_;
    save_wb_cycle(RS);
}

void wb_regfile(rs *RS)
{

    RS->cycles_counter_++;

    if (cdb::available == false)
        return;
    cdb::available = false;
    cdb::rd = RS->res;
    cdb::st = RS;

    save_wb_cycle(RS);
}
void wb_beq(rs *RS)
{
    PC = RS->res;
    save_wb_cycle(RS);
}
void wb_jal_jalr(rs *RS)
{
    PC = RS->inst_->pc + 1;
    wb_regfile(RS);
}
// int NC_WB_LOAD = DEFAULT_NC_WB_LOAD;
// int NC_WB_STORE = DEFAULT_NC_WB_STORE;
// int NC_WB_BEQ = DEFAULT_NC_WB_BEQ;
// int NC_WB_JAL = DEFAULT_NC_WB_JAL;
// int NC_WB_ADD = DEFAULT_NC_WB_ADD;
// int NC_WB_NEG = DEFAULT_NC_WB_NEG;
// int NC_WB_ABS = DEFAULT_NC_WB_ABS;
// int NC_WB_DIV = DEFAULT_NC_WB_DIV;

// void wb_load(rs *RS) {}
// void wb_store(rs *RS) {}
// void wb_beq(rs *RS)
// {

// }
// void wb_add_addi(rs *RS)
// {
// #ifdef DEBUGGING
//     // RS->print();
// #endif

//     RS->cycles_counter_++;

//     if (cdb::available == false)
//         return;
//     RS->inst_->wb_cycle = RS->cycles_counter_ + RS->inst_->exec_finish_cycle;
//     cdb::available = false;
//     cdb::rd = RS->res;
//     cdb::RS = RS;
//     RS->state_ = FINISHED;
// }
// void wb_div(rs *RS)
// {
//     RS->cycles_counter_++;

//     if (cdb::available == false)
//         return;
//     RS->inst_->wb_cycle = RS->cycles_counter_ + RS->inst_->exec_finish_cycle;
//     cdb::available = false;
//     cdb::rd = RS->res;
//     cdb::RS = RS;
// }
// void wb_jal_jalr(rs *RS) {}
// void wb_neg(rs *RS) {}
// void wb_abs(rs *RS) {}

// if (++cycles_counter_ >= nc_wb_ && cdb::available)
// {
//     this->inst_->wb_cycle = cycles_counter_ + this->inst_->exec_finish_cycle;
//     cdb::available = false;
//     wb_(this);
//     reset();
// }