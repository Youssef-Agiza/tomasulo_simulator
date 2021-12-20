#include "defs.hpp"
#include "globals.hpp"
bool can_exec_load(rs *st)
{
    return st->Qj_ == nullptr;

    // if (load_store_buffer.empty()) // gaurd
    //     return false;

    // auto itr = load_store_buffer.begin();
    // while (itr != load_store_buffer.end())
    //     if (*itr++ == st)
    //         return st->Qj_ == nullptr;

    // return false;
    // if (st == load_store_buffer.front())
    //     if (st->Qj_ == nullptr)
    //     {
    //         load_store_buffer.pop_front();
    //         return true;
    //     }
    // for (auto &st0 : load_store_buffer)
    //     if (st0 == st)
    //         return true;
    //     else if (st0->comuted_A_ && st0->imm_)
    //         return false;
}
bool can_exec_store(rs *st)
{
    return st->Qj_ == nullptr;
}
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
