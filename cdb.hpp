#ifndef CDB_H
#define CDB_H
#include "common.hpp"
#include "rs.hpp"

struct cdb
{
    static rs *st;
    static ushort rd;
    static bool available;
};

// extern std::deque<struct CDB> cdb;

#endif
