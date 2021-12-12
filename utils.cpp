#include "defs.hpp"
#include "instruction.hpp"
#include "globals.hpp"

/*****
 *
 * Helper functions
 *
 */
// input: function pointer
// output: iterates on all units and executes the func.
static void iterate_on_stations(void (*func)(rs &st));

// the following three functions use iterate_on_stations
static void update_writing_stations(rs &st);
static void update_non_writing_stations(rs &st);

// input reference to a station
// output: checks if st is waiting for the result in the cdb and updates it.
static void broadcast_to_station(rs &st);
static void update_finished_helper(rs &st);

static void broadcast_to_regstat();

void emit_error(const std::string &err)
{
    std::cerr << "Error: " << err;
    exit(-1);
}
void toupper(std::string &str)
{
    for (auto &c : str)
        c = std::toupper(c);
}

void try_issue(instruction &inst)
{
    if (inst.name == "ADD" || inst.name == "ADDI")
    {
        for (auto &st : rstable.add_addi)
            if (st.state_ == IDLE)
            {
                inst.issue_cycle = cycles;
                st.inst_ = &inst;
                st.issue_(&st);
                PC++;
                break;
            }
    }

    // if (inst.name == "ADD" || inst.name == "ADDI")
    //     for (auto &st : rstable.add_addi)
    //         if (st.state_ == IDLE)
    //         {
    //             st.inst_ = &inst;
    //             st.issue_(&st);
    //             PC++;
    //             break;
    //         }
}

void broadcast()
{
    if (cdb::available) // nothing to broadcast
        return;

    iterate_on_stations(broadcast_to_station);
    broadcast_to_regstat();

    cdb::available = true;
}

void update_stations()
{
    iterate_on_stations(update_writing_stations);
    broadcast();
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

    if (st.state_ == WRITING)
        st.update();
}

static void update_non_writing_stations(rs &st)
{

    if (st.state_ != WRITING)
        st.update();
}

static void broadcast_to_station(rs &st)
{
    if (cdb::st == st.Qk_)
    {
        st.Qk_ = nullptr;
        st.Vk_ = cdb::rd;
    }
    else if (cdb::st == st.Qj_)
    {
        st.Qj_ = nullptr;
        st.Vj_ = cdb::rd;
    }
}

static void broadcast_to_regstat()
{
    for (int r = 0; r < REGFILE_SIZE; r++)
        if (regstat[r].Qi == cdb::st)
        {
            regs[r] = cdb::rd;
            return;
        }
}

static void update_finished_helper(rs &st)
{
    if (st.state_ != IDLE)
        finished = false;
}