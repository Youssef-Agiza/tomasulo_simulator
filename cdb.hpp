#ifndef CDB_H
#define CDB_H
#include "common.hpp"
#include "rs.hpp"

struct CDB
{
    rs *st;
    ushort rd;
    static bool available;
};
bool CDB::available = true;
extern std::deque<struct CDB> cdb;

#endif
