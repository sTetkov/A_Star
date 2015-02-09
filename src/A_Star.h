#ifndef A_STAR_H_INCLUDED
#define A_STAR_H_INCLUDED

#include "DataStructures.h"
#include <functional>

std::vector<PathEdge> A_Star(Node*,Node*,std::function<size_t(Node*,Node*)>);

#endif // A_STAR_H_INCLUDED
