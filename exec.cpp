#include "defs.hpp"
#include "regs.hpp"
#include "rs.hpp"

bool can_exec_load(rs *st)
{
    return true;
}
bool can_exec_store(rs *st) { return true; }
bool can_exec_beq(rs *st) { return true; }
bool can_exec_add_addi(rs *st)
{
    if (st->op_ == ADD_OP)
        return st->Qj_ == nullptr && st->Qk_ == nullptr;
    else if (st->op_ == ADDI_OP)
        return st->Qj_ == nullptr;
    else
        return false;
}
bool can_exec_div(rs *st) { return true; }
bool can_exec_jal_jalr(rs *st) { return true; }
bool can_exec_neg(rs *st) { return true; }
bool can_exec_abs(rs *st) { return true; }