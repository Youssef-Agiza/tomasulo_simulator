#include "defs.hpp"
#include "globals.hpp"

/*****
 *
 * Helper functions
 *
 */

static void update_executing_load_store();
static void update_busy_load_store();
static void broadcast_to_regstat();
static void undo_regstate();

// the following  functions use iterate_on_stations
static void update_writing_stations(rs &st, void *p);
static void update_non_writing_stations(rs &st, void *p);
static void flush_helper(rs &st, void *p);

// input reference to a station
// output: checks if st is waiting for the result in the cdb and updates it.
static void broadcast_to_station(rs &st, void *p);
static void update_finished_helper(rs &st, void *p);

void update_stations()
{
    iterate_on_stations(update_writing_stations);
    update_busy_load_store();
    broadcast();
    update_executing_load_store();
    iterate_on_stations(update_non_writing_stations);
}

void update_program_finished()
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
void flush_stations(uint pc_start)
{
    iterate_on_stations(flush_helper, (void *)&pc_start);
    undo_regstate();
}
void save_regstate()
{
    for (int i = 0; i < REGFILE_SIZE; i++)
        regstat_copy[i].Qi = regstat[i].Qi;
}
/******
 *
 * The following are static helper functions for better readability
 *
 * **********/

static void flush_helper(rs &st, void *p_address)
{
    if (st.state_ == IDLE)
        return;

    uint *pc_address = (uint *)p_address;
    if (st.inst_ != nullptr && st.inst_->pc > *pc_address)
        st.reset();
}
static void undo_regstate()
{
    for (int i = 0; i < REGFILE_SIZE; i++)
        regstat[i].Qi = regstat_copy[i].Qi;
}
static void update_writing_stations(rs &st, void *p)
{

    if (st.state_ == WRITING) // && !(st.inst_->op == LOAD_OP || st.inst_->op == STORE_OP))
        st.update_state();
}

static void update_non_writing_stations(rs &st, void *p)
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
static void update_finished_helper(rs &st, void *p)
{
    if (st.state_ != IDLE)
        finished = false;
}

/****Broad casting helpers*********/
static void broadcast_to_regstat()
{
    for (int r = 1; r < REGFILE_SIZE; r++) // start from 1 to avoid changing R0
        if (regstat[r].Qi == cdb::st)
        {
            regs[r] = cdb::rd;
            regstat[r].Qi = nullptr;
            regstat_copy[r].Qi = nullptr;
            return;
        }
}
static void broadcast_to_station(rs &st, void *p)
{
    if (cdb::st == st.Qk_ && st.inst_->rs2 != 0)
    {
        st.Qk_ = nullptr;
        st.Vk_ = cdb::rd;
    }
    if (cdb::st == st.Qj_ && st.inst_->rs1 != 0)
    {
        st.Qj_ = nullptr;
        st.Vj_ = cdb::rd;
    }
}
