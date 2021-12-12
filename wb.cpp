#include "defs.hpp"
#include "rs.hpp"
#include "regs.hpp"

void wb_load(rs *st) {}
void wb_store(rs *st) {}
void wb_beq(rs *st) {}
void wb_add_addi(rs *st)
{
#ifdef DEBUGGING
    // st->print();
#endif
    for (int i = 0; i < REGFILE_SIZE; i++)
        if (regstat[i].Qi == st)
        {
            switch (st->op_)
            {
            case ADD_OP:
                cdb::rd = st->Vj_ + st->Vk_;
                break;

            case ADDI_OP:
                cdb::rd = st->Vj_ + st->imm_;
                break;
            }
            cdb::st = st;
            return;
        }
}
void wb_div(rs *st) {}
void wb_jal_jalr(rs *st) {}
void wb_neg(rs *st) {}
void wb_abs(rs *st) {}