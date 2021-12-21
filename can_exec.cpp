#include "defs.hpp"
#include "globals.hpp"
bool can_exec_load(rs *RS)
{
    if (branch_issued)
        return false;

    if (load_store_buffer.empty()) // gaurd
        return false;

    return RS == load_store_buffer.front() && RS->Qj_ == nullptr;
}
bool can_exec_store(rs *RS)
{

    if (branch_issued)
        return false;
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
    if (branch_issued)
        return false;

    switch (st->inst_->op)
    {
    case ADD_OP:
        return st->Qj_ == nullptr && st->Qk_ == nullptr;

    case ADDI_OP:
        return st->Qj_ == nullptr;

    default:
        return false;
    }
}
bool can_exec_div(rs *st)
{
    if (branch_issued)
        return false;
    return st->Qj_ == nullptr && st->Qk_ == nullptr;
}
bool can_exec_jal_jalr(rs *st)
{
    if (branch_issued)
        return false;

    switch (st->inst_->op)
    {
    case JALR_OP:
        return st->Qj_ == nullptr;
    case JAL_OP:
        return true;
    default:
        return false;
    }
}
bool can_exec_neg(rs *st)
{
    if (branch_issued)
        return false;
    return st->Qj_ == nullptr;
}
bool can_exec_abs(rs *st)
{
    if (branch_issued)
        return false;
    return st->Qj_ == nullptr;
}