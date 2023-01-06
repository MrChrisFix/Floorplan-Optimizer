#ifndef RESULTSTRUCT_H
#define RESULTSTRUCT_H

#include "Algorithm/Variant.h"
#include <vector>

struct ResultStruct
{
    unsigned bestWidth = -1;
    unsigned bestHeight = -1;
    std::vector<Alg::Variant*> bestCombination;
    long long time_microsec = -1;
};

#endif // RESULTSTRUCT_H

