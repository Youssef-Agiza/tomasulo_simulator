#include "rs.hpp"

int N_LOAD = DEFAULT_N_LOAD;
int N_STORE = DEFAULT_N_STORE;
int N_BEQ = DEFAULT_N_BEQ;
int N_JAL = DEFAULT_N_JAL;
int N_ADD = DEFAULT_N_ADD;
int N_NEG = DEFAULT_N_NEG;
int N_ABS = DEFAULT_N_ABS;
int N_DIV = DEFAULT_N_DIV;

int NC_EXEC_LOAD = DEFAULT_NC_EXEC_LOAD;
int NC_EXEC_STORE = DEFAULT_NC_EXEC_STORE;
int NC_EXEC_BEQ = DEFAULT_NC_EXEC_BEQ;
int NC_EXEC_JAL = DEFAULT_NC_EXEC_JAL;
int NC_EXEC_ADD = DEFAULT_NC_EXEC_ADD;
int NC_EXEC_NEG = DEFAULT_NC_EXEC_NEG;
int NC_EXEC_ABS = DEFAULT_NC_EXEC_ABS;
int NC_EXEC_DIV = DEFAULT_NC_EXEC_DIV;

// number of write back cycles for each station
int NC_WB_LOAD = DEFAULT_NC_WB_LOAD;
int NC_WB_STORE = DEFAULT_NC_WB_STORE;
int NC_WB_BEQ = DEFAULT_NC_WB_BEQ;
int NC_WB_JAL = DEFAULT_NC_WB_JAL;
int NC_WB_ADD = DEFAULT_NC_WB_ADD;
int NC_WB_NEG = DEFAULT_NC_WB_NEG;
int NC_WB_ABS = DEFAULT_NC_WB_ABS;
int NC_WB_DIV = DEFAULT_NC_WB_DIV;

struct RSTable rstable;
std::vector<rs> RSTable::load;
std::vector<rs> RSTable::store;
std::vector<rs> RSTable::beq;
std::vector<rs> RSTable::jal_jalr;
std::vector<rs> RSTable::add_addi;
std::vector<rs> RSTable::neg;
std::vector<rs> RSTable::abs;
std::vector<rs> RSTable::div;

rs::rs(uint nc_exec, uint nc_wb, void (*issue)(rs *), bool (*exec)(rs *), void (*wb)(rs *)) : name_("Default"), nc_exec_(nc_exec), nc_wb_(nc_wb),
                                                                                              issue_(issue), can_exec_(exec), wb_(wb)
{
    this->reset();
}

void rs::print()
{
    using std::setw;
    std::cout << "Name" << setw(10) << setw(10) << "OP" << setw(10) << "Vj" << setw(10) << "Vk" << setw(10) << "Qj" << setw(10) << "Qk" << setw(10) << "A\n";
    std::cout << name_ << setw(10) << setw(10) << op_ << setw(10) << Vj_ << setw(10) << Vk_ << setw(10) << Qj_ << setw(10) << Qk_ << setw(10) << A_ << "\n";
}

void rs::reset()
{
    state_ = IDLE;
    inst_ = nullptr;

    cycles_counter_ = 0;

    Vj_ = -1;
    Qj_ = nullptr;

    Vk_ = -1;
    Qk_ = nullptr;
}
void rs::update()
{
    switch (this->state_)
    {
    case IDLE:
        return;
    case BUSY: // issued didn't start exec
    {
        cycles_counter_++;
        if (can_exec_(this))
        {
            this->inst_->exec_start_cycle = cycles_counter_ + this->inst_->issue_cycle;
            this->state_ = EXECUTING;
            cycles_counter_ = 0;
        }
        return;
    };

    case EXECUTING:
    {

        if (++cycles_counter_ >= nc_exec_)
        {
            this->inst_->exec_finish_cycle = cycles_counter_ + this->inst_->exec_start_cycle;
            this->state_ = WRITING;
            cycles_counter_ = 0;
        }
        return;
    }

    case WRITING:
    {
        if (++cycles_counter_ >= nc_wb_ && cdb::available)
        {
            this->inst_->wb_cycle = cycles_counter_ + this->inst_->exec_finish_cycle;
            cdb::available = false;
            wb_(this);
            reset();
        }

        return;
    }

    case FINISHED:
        reset();
        return;
    }
}

void initalize_station_name(std::vector<rs> &stations, const std::string &base_name)
{
    int count = 0;
    for (auto &st : stations)
        st.name_ = base_name + std::to_string(count++);
}
void initalize_rstable()
{
    rstable.load.resize(N_LOAD, rs(NC_EXEC_LOAD, NC_WB_LOAD, issue_load, can_exec_load, wb_load));
    initalize_station_name(rstable.load, "LOAD");

    rstable.store.resize(N_STORE, rs(NC_EXEC_STORE, NC_WB_STORE, issue_store, can_exec_store, wb_store));
    initalize_station_name(rstable.store, "STORE");

    rstable.beq.resize(N_BEQ, rs(NC_EXEC_BEQ, NC_WB_BEQ, issue_beq, can_exec_beq, wb_beq));
    initalize_station_name(rstable.beq, "BEQ");

    rstable.jal_jalr.resize(N_JAL, rs(NC_EXEC_JAL, NC_WB_JAL, issue_jal_jalr, can_exec_jal_jalr, wb_jal_jalr));
    initalize_station_name(rstable.jal_jalr, "JAL/JALR");

    rstable.abs.resize(N_ABS, rs(NC_EXEC_ABS, NC_WB_ABS, issue_abs, can_exec_abs, wb_abs));
    initalize_station_name(rstable.abs, "ABS");

    rstable.neg.resize(N_NEG, rs(NC_EXEC_NEG, NC_WB_NEG, issue_neg, can_exec_neg, wb_neg));
    initalize_station_name(rstable.neg, "NEG");

    rstable.add_addi.resize(N_ADD, rs(NC_EXEC_ADD, NC_WB_ADD, issue_add_addi, can_exec_add_addi, wb_add_addi));
    initalize_station_name(rstable.add_addi, "ADD/ADDI");

    rstable.div.resize(N_DIV, rs(NC_EXEC_DIV, NC_WB_DIV, issue_div, can_exec_div, wb_div));
    initalize_station_name(rstable.div, "DIV");
}
void get_dynamic_hardware_params()
{
    // left empty for now
}