#ifndef RESULTSTRUCT_H
#define RESULTSTRUCT_H

#include "Algorithm/Variant.h"
#include <vector>

struct ResultStruct
{
    unsigned bestWidth;
    unsigned bestHeight;
    std::vector<Alg::Variant*> bestCombination;
};

#endif // RESULTSTRUCT_H

