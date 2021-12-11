#include "defs.hpp"
#include "rs.hpp"
#include "regs.hpp"

void wb_load(rs *st) {}
void wb_store(rs *st) {}
void wb_beq(rs *st) {}
void wb_add_addi(rs *st)
{
    st->print();
    for (int i = 0; i < REGFILE_SIZE; i++)
        if (regstat[i].Qi == st)
        {
            switch (st->op_)
            {
            case ADD_OP:
                regs[i] = st->Vj_ + st->Vk_;
                break;

            case ADDI_OP:
                regs[i] = st->Vj_ + st->imm_;
                break;
            }
            return;
        }
}
void wb_div(rs *st) {}
void wb_jal_jalr(rs *st) {}
void wb_neg(rs *st) {}
void wb_abs(rs *st) {}