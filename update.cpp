#include "defs.hpp"
#include "globals.hpp"

/*****
 *
 * Helper functions
 *
 */
// input: function pointer
// output: iterates on all units and executes the func.
static void iterate_on_stations(void (*func)(rs &st));

static void update_executing_load_store();
static void update_busy_load_store();
// the following three functions use iterate_on_stations
static void update_writing_stations(rs &st);
static void update_non_writing_stations(rs &st);

// input reference to a station
// output: checks if st is waiting for the result in the cdb and updates it.
static void broadcast_to_station(rs &st);
static void update_finished_helper(rs &st);

static void broadcast_to_regstat();

void update_stations()
{
    iterate_on_stations(update_writing_stations);
    update_executing_load_store();
    broadcast();
    update_busy_load_store();
    iterate_on_stations(update_non_writing_stations);
}

void update_finished()
{
    finished = true;
    if (PC < inst_mem.size())
    {
        finished = false;
        return;
    }

    iterate_on_stations(update_finished_helper);
}

void broadcast()
{
    if (cdb::available) // nothing to broadcast
        return;

    iterate_on_stations(broadcast_to_station);
    broadcast_to_regstat();

    cdb::available = true;
}

/******
 *
 * The following are static helper functions for better readability
 *
 * **********/

static void iterate_on_stations(void (*func)(rs &st))
{

    for (auto &st : rstable.load)
        func(st);

    for (auto &st : rstable.store)
        func(st);

    for (auto &st : rstable.add_addi)
        func(st);

    for (auto &st : rstable.abs)
        func(st);

    for (auto &st : rstable.beq)
        func(st);

    for (auto &st : rstable.div)
        func(st);

    for (auto &st : rstable.jal_jalr)
        func(st);

    for (auto &st : rstable.neg)
        func(st);
}

static void update_writing_stations(rs &st)
{

    if (st.state_ == WRITING) // && !(st.inst_->op == LOAD_OP || st.inst_->op == STORE_OP))
        st.update_state();
}

static void update_non_writing_stations(rs &st)
{

    if (st.state_ == IDLE)
        return;

    if (st.state_ != WRITING && !(st.inst_->op == LOAD_OP || st.inst_->op == STORE_OP))
        st.update_state();
}

static void update_executing_load_store()
{
    for (auto &st : rstable.load)
        if (st.state_ == EXECUTING)
            st.update_state();

    for (auto &st : rstable.store)
        if (st.state_ == EXECUTING)
            st.update_state();
}
static void update_busy_load_store()
{
    for (auto &st : rstable.load)
        if (st.state_ == BUSY)
            st.update_state();

    for (auto &st : rstable.store)
        if (st.state_ == BUSY)
            st.update_state();
}
static void update_finished_helper(rs &st)
{
    if (st.state_ != IDLE)
        finished = false;
}

/****Broad casting helpers*********/
static void broadcast_to_regstat()
{
    for (int r = 0; r < REGFILE_SIZE; r++)
        if (regstat[r].Qi == cdb::st)
        {
            regs[r] = cdb::rd;
            return;
        }
}
static void broadcast_to_station(rs &st)
{
    if (cdb::st == st.Qk_)
    {
        st.Qk_ = nullptr;
        st.Vk_ = cdb::rd;
    }
    if (cdb::st == st.Qj_)
    {
        st.Qj_ = nullptr;
        st.Vj_ = cdb::rd;
    }
}
