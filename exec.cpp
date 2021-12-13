#include "defs.hpp"
#include "globals.hpp"

int NC_EXEC_LOAD = DEFAULT_NC_EXEC_LOAD;
int NC_EXEC_STORE = DEFAULT_NC_EXEC_STORE;
int NC_EXEC_BEQ = DEFAULT_NC_EXEC_BEQ;
int NC_EXEC_JAL = DEFAULT_NC_EXEC_JAL;
int NC_EXEC_ADD = DEFAULT_NC_EXEC_ADD;
int NC_EXEC_NEG = DEFAULT_NC_EXEC_NEG;
int NC_EXEC_ABS = DEFAULT_NC_EXEC_ABS;
int NC_EXEC_DIV = DEFAULT_NC_EXEC_DIV;

void exec_load(rs *st) {}
void exec_store(rs *st) {}
void exec_beq(rs *st) {}
void exec_add_addi(rs *st)
{
    if (++st->cycles_counter_ >= NC_EXEC_ADD)
    {
        switch (st->op_)
        {
        case ADD_OP:
            st->res = st->Vj_ + st->Vk_;
            break;

        case ADDI_OP:
            st->res = st->Vj_ + st->imm_;
            break;
        }

        st->inst_->exec_finish_cycle = st->cycles_counter_ + st->inst_->exec_start_cycle;
        st->state_ = WRITING;
        st->cycles_counter_ = 0;
    }
}
void exec_div(rs *st) {}
void exec_jal_jalr(rs *st) {}
void exec_neg(rs *st) {}
void exec_abs(rs *st) {}