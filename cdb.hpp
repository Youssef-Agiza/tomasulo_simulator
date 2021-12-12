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
<<<<<<< HEAD

// extern std::deque<struct CDB> cdb;
=======
// bool CDB::available = true;
extern std::deque<struct CDB> cdb;
>>>>>>> 36bc7d1f224494750c3028f84d6935611f593660

#endif
