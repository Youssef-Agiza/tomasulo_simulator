#include "rs.hpp"

int N_LOAD = DEFAULT_N_LOAD;
int N_STORE = DEFAULT_N_STORE;
int N_BEQ = DEFAULT_N_BEQ;
int N_JAL = DEFAULT_N_JAL;
int N_ADD = DEFAULT_N_ADD;
int N_NEG = DEFAULT_N_NEG;
int N_ABS = DEFAULT_N_ABS;
int N_DIV = DEFAULT_N_DIV;

struct RSTable rstable;
std::vector<rs> RSTable::load;
std::vector<rs> RSTable::store;
std::vector<rs> RSTable::beq;
std::vector<rs> RSTable::jal_jalr;
std::vector<rs> RSTable::add_addi;
std::vector<rs> RSTable::neg;
std::vector<rs> RSTable::abs;
std::vector<rs> RSTable::div;

rs::rs( // uint nc_exec, uint nc_wb,
    void (*issue)(rs *), bool (*can_exec)(rs *),
    void (*exec)(rs *), void (*wb)(rs *)) : name_("DEFAULT"),
                                            // nc_exec_(nc_exec), nc_wb_(nc_wb),
                                            issue_(issue), can_exec_(can_exec),
                                            exec_(exec), wb_(wb)
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

    comuted_A_ = false;
}
void rs::update_state()
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
        exec_(this);

        // if (++cycles_counter_ >= nc_exec_)
        // {
        //     this->inst_->exec_finish_cycle = cycles_counter_ + this->inst_->exec_start_cycle;
        //     this->state_ = WRITING;
        //     this->imm_ = this->imm_ + this->Vj_;
        //     cycles_counter_ = 0;
        // }
        if (this->state_ != FINISHED)
            return;
    }

    case WRITING:
    {
        if (wb_ != nullptr)
            wb_(this);
        else
            state_ = FINISHED;
        // if (++cycles_counter_ >= nc_wb_ && cdb::available)
        // {
        //     this->inst_->wb_cycle = cycles_counter_ + this->inst_->exec_finish_cycle;
        //     cdb::available = false;
        //     wb_(this);
        //     reset();
        // }
        if (this->state_ != FINISHED)
            return;
    }

    case FINISHED:
    {
        reset();
        return;
    }
    }
}

void rs::issue(instruction &inst)
{
    inst.issue_cycle = cycles;
    this->inst_ = &inst;
    this->issue_(this);
}

void initalize_station_name(std::vector<rs> &stations, const std::string &base_name)
{
    int count = 0;
    for (auto &st : stations)
        st.name_ = base_name + std::to_string(count++);
}
void initalize_rstable()
{
    rstable.load.resize(N_LOAD, rs( // NC_EXEC_LOAD, NC_WB_LOAD,
                                    issue_load, can_exec_load, exec_load, wb_regfile));
    initalize_station_name(rstable.load, "LOAD");

    rstable.store.resize(N_STORE, rs( // NC_EXEC_STORE, NC_WB_STORE,
                                      issue_store, can_exec_store, exec_store, wb_mem));
    initalize_station_name(rstable.store, "STORE");

    rstable.beq.resize(N_BEQ, rs( // NC_EXEC_BEQ, NC_WB_BEQ,
                                  issue_beq, can_exec_beq, exec_beq, wb_beq));
    initalize_station_name(rstable.beq, "BEQ");

    rstable.jal_jalr.resize(N_JAL, rs( // NC_EXEC_JAL, NC_WB_JAL,
                                       issue_jal_jalr, can_exec_jal_jalr, exec_jal_jalr, wb_jal_jalr));
    initalize_station_name(rstable.jal_jalr, "JAL/JALR");

    rstable.abs.resize(N_ABS, rs( // NC_EXEC_ABS, NC_WB_ABS,
                                  issue_abs, can_exec_abs, exec_abs, wb_regfile));
    initalize_station_name(rstable.abs, "ABS");

    rstable.neg.resize(N_NEG, rs( // NC_EXEC_NEG, NC_WB_NEG,
                                  issue_neg, can_exec_neg, exec_neg, wb_regfile));
    initalize_station_name(rstable.neg, "NEG");

    rstable.add_addi.resize(N_ADD, rs( // NC_EXEC_ADD, NC_WB_ADD,
                                       issue_add_addi, can_exec_add_addi, exec_add_addi, wb_regfile));
    initalize_station_name(rstable.add_addi, "ADD/ADDI");

    rstable.div.resize(N_DIV, rs( // NC_EXEC_DIV, NC_WB_DIV,
                                  issue_div, can_exec_div, exec_div, wb_regfile));
    initalize_station_name(rstable.div, "DIV");
}
void get_dynamic_hardware_params()

{
    char answer = 'x';
    std::cout << "Do you want to customize the hardware?(y/n)";
    std::cin >> answer;
    answer = toupper(answer);
    while (answer != 'Y' && answer != 'N')
    {
        "Enter a valid answer!\n";
        std::cout << "Do you want to customize the hardware?(y/n)";
        std::cin >> answer;
        answer = toupper(answer);
    }
    if (answer == 'Y')
    {
        std::cout << "Enter NC for div: ";
        std::cin >> NC_EXEC_DIV;
    }
    // left empty for now
}