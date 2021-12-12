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

bool cdb::available = true;
ushort cdb::rd = -1;
rs *cdb::st = nullptr

// extern std::deque<struct CDB> cdb;

#endif
