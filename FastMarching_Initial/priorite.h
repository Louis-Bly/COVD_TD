#pragma once
#include <vector>
#include "pointDist.h"

class FilePriorite {
    std::vector<PointDist> v;
public:
    FilePriorite();
    void push(PointDist d);
    PointDist pop();
    bool empty() const;
};
