#ifndef RS_H
#define RS_H
#include "common.hpp"
#include "params.h"
#include "defs.hpp"
#include "globals.hpp"

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
    int cycles_counter_;

    std::string name_;
    ushort op_;

    short Vj_;
    rs *Qj_;

    short Vk_;
    rs *Qk_;

    int imm_;
    ushort A_; // address
    bool comuted_A_;
    bool branch_taken_;

    int res; // result

private:
    void (*issue_)(rs *);
    bool (*can_exec_)(rs *);
    void (*exec_)(rs *);
    void (*wb_)(rs *);

public:
    rs( // uint exec_cycles, uint wb_cycles,
        void (*issue)(rs *), bool (*can_exec)(rs *), void (*exec)(rs *), void (*wb)(rs *));
    void reset();

    void issue(instruction &inst);
    void update_state();

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