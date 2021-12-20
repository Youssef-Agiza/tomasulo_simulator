#include "defs.hpp"
#include "globals.hpp"
bool can_exec_load(rs *RS)
{
    // return RS->Qj_ == nullptr;

    if (load_store_buffer.empty()) // gaurd
        return false;

    return RS == load_store_buffer.front() && RS->Qj_ == nullptr;

    // auto itr = load_store_buffer.begin();
    // while (itr != load_store_buffer.end())
    //     if (*itr++ == RS)
    //         return RS->Qj_ == nullptr;

    // return false;
    //     if (RS->Qj_ == nullptr)
    //     {
    //         load_store_buffer.pop_front();
    //         return true;
    //     }
}
bool can_exec_store(rs *RS)
{
    if (load_store_buffer.empty()) // gaurd
        return false;

    return RS == load_store_buffer.front() && RS->Qj_ == nullptr;
}
bool can_exec_beq(rs *st)
{
    return st->Qj_ == nullptr && st->Qk_ == nullptr;
}
bool can_exec_add_addi(rs *st)
{
    if (st->op_ == ADD_OP)
        return st->Qj_ == nullptr && st->Qk_ == nullptr;
    else if (st->op_ == ADDI_OP)
        return st->Qj_ == nullptr;
    else
        return false;
}
bool can_exec_div(rs *st)
{
    return st->Qj_ == nullptr && st->Qk_ == nullptr;
}
bool can_exec_jal_jalr(rs *st)
{
    if (st->op_ == JALR_OP)
        return st->Qj_ == nullptr;
    else if (st->op_ == JAL_OP)
        return true;
    else
        return false;
}
bool can_exec_neg(rs *st)
{
    return st->Qj_ == nullptr;
}
bool can_exec_abs(rs *st)
{
    return st->Qj_ == nullptr;
}