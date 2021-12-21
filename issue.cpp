#include "defs.hpp"
#include "rs.hpp"
#include "regs.hpp"

static instruction *inst;

void issue_load(rs *st)
{
    inst = st->inst_;
    st->state_ = BUSY;

    if (regstat[inst->rs1].Qi != nullptr)
        st->Qj_ = regstat[inst->rs1].Qi;
    else
    {
        st->Vj_ = regs[inst->rs1];
        st->Qj_ = nullptr;
    }
    st->imm_ = inst->imm;
    regstat[inst->rd].Qi = st;
}

void issue_store(rs *st)
{
    inst = st->inst_;
    st->state_ = BUSY;

    if (regstat[inst->rs1].Qi != nullptr)
        st->Qj_ = regstat[inst->rs1].Qi;
    else
    {
        st->Vj_ = regs[inst->rs1];
        st->Qj_ = nullptr;
    }
    if (regstat[inst->rs2].Qi != nullptr)
        st->Qk_ = regstat[inst->rs2].Qi;
    else
    {
        st->Vk_ = regs[inst->rs2];
        st->Qk_ = nullptr;
    }
    st->imm_ = inst->imm;
}

void issue_beq(rs *st)
{
    if (branch_issued)
    {
        stall = true;
        PC--; // undo pc incrementation
        return;
    }

    inst = st->inst_;
    st->state_ = BUSY;

    branch_issued = true;
    save_regstate();

    if (regstat[inst->rs1].Qi != nullptr)
        st->Qj_ = regstat[inst->rs1].Qi;
    else
    {
        st->Vj_ = regs[inst->rs1];
        st->Qj_ = nullptr;
    }
    if (regstat[inst->rs2].Qi != nullptr)
        st->Qk_ = regstat[inst->rs2].Qi;
    else
    {
        st->Vk_ = regs[inst->rs2];
        st->Qk_ = nullptr;
    }
    st->imm_ = inst->imm;
}

void issue_jal_jalr(rs *st)
{
    inst = st->inst_;
    st->state_ = BUSY;

    if (inst->name == "JALR")
    {

        if (regstat[inst->rs1].Qi != nullptr)
            st->Qk_ = regstat[inst->rs1].Qi;
        else
        {
            st->Vj_ = regs[inst->rs1];
            st->Qk_ = nullptr;
        }
        st->op_ = JALR_OP;
    }
    else if (inst->name == "JAL")
    {

        st->imm_ = inst->imm;
        st->op_ = JAL_OP;
    }

    regstat[inst->rd].Qi = st;
}

void issue_add_addi(rs *st)
{

    inst = st->inst_;
    st->state_ = BUSY;

    if (regstat[inst->rs1].Qi != nullptr)
        st->Qj_ = regstat[inst->rs1].Qi;
    else
    {
        st->Vj_ = regs[inst->rs1];
        st->Qj_ = nullptr;
    }
    if (inst->name == "ADD")
    {

        if (regstat[inst->rs2].Qi != nullptr)
            st->Qk_ = regstat[inst->rs2].Qi;
        else
        {
            st->Vk_ = regs[inst->rs2];
            st->Qk_ = nullptr;
        }
        st->op_ = ADD_OP;
    }
    else if (inst->name == "ADDI")
    {

        st->imm_ = inst->imm;
        st->op_ = ADDI_OP;
    }

    regstat[inst->rd].Qi = st;
}
void issue_div(rs *st)
{
    inst = st->inst_;
    st->state_ = BUSY;

    if (regstat[inst->rs1].Qi != nullptr)
        st->Qj_ = regstat[inst->rs1].Qi;
    else
    {
        st->Vj_ = regs[inst->rs1];
        st->Qj_ = nullptr;
    }

    if (regstat[inst->rs2].Qi != nullptr)
        st->Qk_ = regstat[inst->rs2].Qi;
    else
    {
        st->Vk_ = regs[inst->rs2];
        st->Qk_ = nullptr;
    }
    regstat[inst->rd].Qi = st;
}

void issue_neg(rs *st)
{
    inst = st->inst_;
    st->state_ = BUSY;

    if (regstat[inst->rs1].Qi != nullptr)
        st->Qj_ = regstat[inst->rs1].Qi;
    else
    {
        st->Vj_ = regs[inst->rs1];
        st->Qj_ = nullptr;
    }
    regstat[inst->rd].Qi = st;
}
void issue_abs(rs *st)
{
    inst = st->inst_;
    st->state_ = BUSY;

    if (regstat[inst->rs1].Qi != nullptr)
        st->Qj_ = regstat[inst->rs1].Qi;
    else
    {
        st->Vj_ = regs[inst->rs1];
        st->Qj_ = nullptr;
    }
    regstat[inst->rd].Qi = st;
}

void try_issue(instruction &p_inst)
{
    if (p_inst.name == "LOAD")
        for (auto &st : rstable.load)
            if (st.state_ == IDLE)
            {
                load_store_buffer.push_back(&st);
                st.issue(p_inst);
                PC++;
                return;
            }

    if (p_inst.name == "STORE")
        for (auto &st : rstable.store)
            if (st.state_ == IDLE)
            {
                load_store_buffer.push_back(&st);
                st.issue(p_inst);
                PC++;
                return;
            }

    if (p_inst.name == "BEQ")
        for (auto &st : rstable.beq)
            if (st.state_ == IDLE)
            {
                st.issue(p_inst);
                PC++;
                return;
            }

    if (p_inst.name == "JAL" || p_inst.name == "JALR")
        for (auto &st : rstable.jal_jalr)
            if (st.state_ == IDLE)
            {
                p_inst.pc = PC;
                st.issue(p_inst);
                stall = true;
                return;
            }

    if (p_inst.name == "NEG")
        for (auto &st : rstable.neg)
            if (st.state_ == IDLE)
            {
                st.issue(p_inst);
                PC++;
                return;
            }

    if (p_inst.name == "DIV")
        for (auto &st : rstable.div)
            if (st.state_ == IDLE)
            {
                st.issue(p_inst);
                PC++;
                return;
            }

    if (p_inst.name == "ABS")
        for (auto &st : rstable.abs)
            if (st.state_ == IDLE)
            {
                st.issue(p_inst);
                PC++;
                return;
            }

    if (p_inst.name == "ADD" || p_inst.name == "ADDI")
        for (auto &st : rstable.add_addi)
            if (st.state_ == IDLE)
            {
                st.issue(p_inst);
                PC++;
                return;
            }
}
