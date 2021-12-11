#ifndef RS_H
#define RS_H
#include "common.hpp"
#include "params.h"
#include "defs.hpp"
#include "instruction.hpp"

// number of stations for each unit
extern int N_LOAD;
extern int N_STORE;
extern int N_BEQ;
extern int N_JAL;
extern int N_ADD;
extern int N_NEG;
extern int N_ABS;
extern int N_DIV;

// number of execution cycles for each station
extern int NC_EXEC_LOAD;
extern int NC_EXEC_STORE;
extern int NC_EXEC_BEQ;
extern int NC_EXEC_JAL;
extern int NC_EXEC_ADD;
extern int NC_EXEC_NEG;
extern int NC_EXEC_ABS;
extern int NC_EXEC_DIV;

// number of write back cycles for each station
extern int NC_WB_LOAD;
extern int NC_WB_STORE;
extern int NC_WB_BEQ;
extern int NC_WB_JAL;
extern int NC_WB_ADD;
extern int NC_WB_NEG;
extern int NC_WB_ABS;
extern int NC_WB_DIV;

enum rsstate
{
    IDLE = 0,
    BUSY,
    EXECUTING,
    WRITING,
    FINISHED
};

class rs //  reservation station
{
public:
    struct instruction *inst_;
    enum rsstate state_;
    uint cycles_counter_;
    uint exec_cycles_;
    uint wb_cycles_;

    std::string name_;
    bool busy_;
    bool finished_exec_;
    ushort op_;

    ushort Vj_;
    rs *Qj_;

    ushort Vk_;
    rs *Qk_;

    uint imm_;
    ushort A_; // address

    rs(uint exec_cycles, uint wb_cycles, void (*issue)(rs *), bool (*exec)(rs *), void (*wb)(rs *));
    void reset();

    void (*issue_)(rs *);
    bool (*can_exec_)(rs *);
    void (*wb_)(rs *);

    void update();

    void print();
};

struct RSTable
{
    static std::vector<rs> load;
    static std::vector<rs> store;
    static std::vector<rs> beq;
    static std::vector<rs> jal_jalr;
    static std::vector<rs> add_addi;
    static std::vector<rs> neg;
    static std::vector<rs> abs;
    static std::vector<rs> div;
};
extern RSTable rstable;

#endif