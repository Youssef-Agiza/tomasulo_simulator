#include "defs.hpp"
#include "rs.hpp"
#include "regs.hpp"

int NC_WB_REGFILE = DEFAULT_NC_WB_REGFILE;
int NC_WB_MEM = DEFAULT_NC_WB_MEM;

static void record_wb_cycle(rs *RS)
{
    RS->inst_->wb_cycle = RS->cycles_counter_ + RS->inst_->exec_finish_cycle;
    RS->state_ = FINISHED;
}
static void lock_cdb(rs *RS)
{
    cdb::available = false;
    cdb::rd = RS->res;
    cdb::st = RS;
}

void wb_mem(rs *RS)
{
    ++RS->cycles_counter_;
    if (RS->Qk_ != nullptr || RS->cycles_counter_ < NC_WB_MEM)
        return;

    data_mem[RS->imm_ % MEMORY_SIZE] = RS->Vk_;
    record_wb_cycle(RS);
}

void wb_regfile(rs *RS)
{

    if (++RS->cycles_counter_ < NC_WB_REGFILE || cdb::available == false)
        return;

    lock_cdb(RS);
    record_wb_cycle(RS);
}
void wb_beq(rs *RS)
{
    if (RS->branch_taken_)
    {
        flush_stations(RS->inst_->pc);
        stall = false;
        PC = RS->res;
    }
    record_wb_cycle(RS);
}
void wb_jal_jalr(rs *RS)
{
    if (++RS->cycles_counter_ < NC_WB_REGFILE || cdb::available == false)
        return;

    PC = RS->res;
    stall = false;
    RS->res = RS->inst_->pc + 1;
    lock_cdb(RS);

    record_wb_cycle(RS);
}