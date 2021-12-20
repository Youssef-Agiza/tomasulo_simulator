#include "defs.hpp"
#include "rs.hpp"
#include "regs.hpp"

int NC_WB_REGFILE = DEFAULT_NC_WB_REGFILE;
int NC_WB_MEM = DEFAULT_NC_WB_MEM;

void wb_mem(rs *st)
{
    ++st->cycles_counter_;
    if (st->Qk_ != nullptr || st->cycles_counter_ < NC_WB_MEM)
        return;

    data_mem[st->res % MEMORY_SIZE] = st->Vk_;
    st->inst_->wb_cycle = st->cycles_counter_ + st->inst_->exec_finish_cycle;
    st->state_ = FINISHED;
}

void wb_regfile(rs *st)
{

    st->cycles_counter_++;

    if (cdb::available == false)
        return;
    cdb::available = false;
    cdb::rd = st->res;
    st->inst_->wb_cycle = st->cycles_counter_ + st->inst_->exec_finish_cycle;
    cdb::st = st;
    st->state_ = FINISHED;
}

// int NC_WB_LOAD = DEFAULT_NC_WB_LOAD;
// int NC_WB_STORE = DEFAULT_NC_WB_STORE;
// int NC_WB_BEQ = DEFAULT_NC_WB_BEQ;
// int NC_WB_JAL = DEFAULT_NC_WB_JAL;
// int NC_WB_ADD = DEFAULT_NC_WB_ADD;
// int NC_WB_NEG = DEFAULT_NC_WB_NEG;
// int NC_WB_ABS = DEFAULT_NC_WB_ABS;
// int NC_WB_DIV = DEFAULT_NC_WB_DIV;

// void wb_load(rs *st) {}
// void wb_store(rs *st) {}
// void wb_beq(rs *st)
// {

// }
// void wb_add_addi(rs *st)
// {
// #ifdef DEBUGGING
//     // st->print();
// #endif

//     st->cycles_counter_++;

//     if (cdb::available == false)
//         return;
//     st->inst_->wb_cycle = st->cycles_counter_ + st->inst_->exec_finish_cycle;
//     cdb::available = false;
//     cdb::rd = st->res;
//     cdb::st = st;
//     st->state_ = FINISHED;
// }
// void wb_div(rs *st)
// {
//     st->cycles_counter_++;

//     if (cdb::available == false)
//         return;
//     st->inst_->wb_cycle = st->cycles_counter_ + st->inst_->exec_finish_cycle;
//     cdb::available = false;
//     cdb::rd = st->res;
//     cdb::st = st;
// }
// void wb_jal_jalr(rs *st) {}
// void wb_neg(rs *st) {}
// void wb_abs(rs *st) {}

// if (++cycles_counter_ >= nc_wb_ && cdb::available)
// {
//     this->inst_->wb_cycle = cycles_counter_ + this->inst_->exec_finish_cycle;
//     cdb::available = false;
//     wb_(this);
//     reset();
// }