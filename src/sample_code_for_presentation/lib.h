#include "record.h"
#include <memory>

inline void ProcessRecord(Record* record)
{
    // Do something with the record here ...
    delete record;
}

inline void ProcessRecord(std::shared_ptr<Record> record)
{
    // Do something with the record here ...
}