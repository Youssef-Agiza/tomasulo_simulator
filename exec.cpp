#include "defs.hpp"
#include "globals.hpp"

int NC_EXEC_ADDRESS_LOAD = DEFAULT_NC_EXEC_ADDRESS_LOAD;
int NC_EXEC_MEM_LOAD = DEFAULT_NC_EXEC_MEM_LOAD;
int NC_EXEC_STORE = DEFAULT_NC_EXEC_STORE;
int NC_EXEC_BEQ = DEFAULT_NC_EXEC_BEQ;
int NC_EXEC_JAL = DEFAULT_NC_EXEC_JAL;
int NC_EXEC_ADD = DEFAULT_NC_EXEC_ADD;
int NC_EXEC_NEG = DEFAULT_NC_EXEC_NEG;
int NC_EXEC_ABS = DEFAULT_NC_EXEC_ABS;
int NC_EXEC_DIV = DEFAULT_NC_EXEC_DIV;

static void record_finish_exec_cycle(rs *RS)
{
    RS->inst_->exec_finish_cycle = RS->cycles_counter_ + RS->inst_->exec_start_cycle;
    RS->state_ = WRITING;
    RS->cycles_counter_ = 0;
}
static bool is_address_conflict(rs *RS)
{
    if (!RS->comuted_A_) // prevent calling this function before computing A
        return true;

    if (RS->inst_->op == STORE_OP)
        for (auto &st : rstable.load)
        {
            if (&st == RS)
                break;
            if (st.state_ == IDLE || !st.comuted_A_)
                continue;

            if (st.imm_ == RS->imm_)
                return true;
        }

    for (auto &st : rstable.store)
    {
        if (&st == RS)
            break;

        if (st.state_ == IDLE || !st.comuted_A_)
            continue;

        if (st.imm_ == RS->imm_)
            return true;
    }
    return false;
    // for (auto &st : load_store_buffer)
    //     if (st == RS) // reached RS without conflicts
    //         break;
    //     else if (RS->inst_->op == LOAD_OP && st->inst_->op == LOAD_OP) // skip loads if RS is load
    //         continue;
    //     else if (!st->comuted_A_ && st->state_ != IDLE) // found a station before the current that didn't finish computing A
    //         return true;
    //     else if (st->imm_ == RS->imm_ && st->state_ != IDLE) // found a conflict
    //         return true;
}

void exec_load(rs *RS)
{

    if (++RS->cycles_counter_ < NC_EXEC_ADDRESS_LOAD)
        return;
    if (!RS->comuted_A_)
    {
        if (RS != load_store_buffer.front())
            emit_error("Executing load(step1) that is not the head of the buffer");
        load_store_buffer.pop_front();

        RS->comuted_A_ = true;
        RS->imm_ = RS->Vj_ + RS->imm_;
        return;
    }

    if (is_address_conflict(RS))
        return;

    if (RS->cycles_counter_ >= NC_EXEC_MEM_LOAD + NC_EXEC_ADDRESS_LOAD)
    {
        RS->res = data_mem[RS->imm_ % MEMORY_SIZE];
        record_finish_exec_cycle(RS);
    }
}
void exec_store(rs *RS)
{
    if (++RS->cycles_counter_ < NC_EXEC_STORE)
        return;

    if (!RS->comuted_A_)
    {
        if (RS != load_store_buffer.front())
            emit_error("Executing store that is not the head of the buffer");
        load_store_buffer.pop_front();

        RS->comuted_A_ = true;
        RS->imm_ = RS->Vj_ + RS->imm_;
    }

    if (is_address_conflict(RS))
        return;

    RS->res = RS->Vj_; //+ RS->imm_;
    record_finish_exec_cycle(RS);
}

void exec_add_addi(rs *RS)
{
    if (++RS->cycles_counter_ >= NC_EXEC_ADD)
    {
        switch (RS->op_)
        {
        case ADD_OP:
            RS->res = RS->Vj_ + RS->Vk_;
            break;

        case ADDI_OP:
            RS->res = RS->Vj_ + RS->imm_;
            break;
        }
        record_finish_exec_cycle(RS);
    }
}
void exec_div(rs *RS)
{
    if (++RS->cycles_counter_ >= NC_EXEC_DIV)
    {
        RS->res = (RS->Vk_ != 0) ? (RS->Vj_ / RS->Vk_) : (-1);

        record_finish_exec_cycle(RS);
    }
}
void exec_beq(rs *RS)
{

    if (++RS->cycles_counter_ >= NC_EXEC_BEQ)
    {
        if (RS->Vj_ == RS->Vk_)
        {
            RS->res = RS->inst_->pc + RS->imm_ + 1;
            flush_stations(RS->inst_->pc);
        }

        branch_issued = false;
        record_finish_exec_cycle(RS);
    }
}
void exec_jal_jalr(rs *RS)
{
    if (++RS->cycles_counter_ >= NC_EXEC_JAL)
    {
        switch (RS->inst_->op)
        {
        case JAL_OP:
        {
            // RS->res = RS->inst_->pc + 1;
            RS->res = RS->imm_ + 1 + PC;
            break;
        }
        case JALR_OP:
        {
            // RS->res = RS->inst_->pc + 1;
            RS->res = RS->Vj_;
            break;
        }
        default:
            break;
        }
        stall = false;
        record_finish_exec_cycle(RS);
    }
}
void exec_neg(rs *RS)
{
    if (++RS->cycles_counter_ >= NC_EXEC_NEG)
    {
        RS->res = (~RS->Vj_) + 1;
        record_finish_exec_cycle(RS);
    }
}
void exec_abs(rs *RS)
{
    if (++RS->cycles_counter_ >= NC_EXEC_ABS)
    {
        RS->res = (((signed short)RS->Vj_) < 0) ? -RS->Vj_ : RS->Vj_;
        record_finish_exec_cycle(RS);
    }
}