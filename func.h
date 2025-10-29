#pragma once
#include "class.h"

node* uniform_cost(std::vector<node*>& frontier);

node* Astar_misplaced(std::vector<node*>& frontier);

node* Astar_Euclidean(std::vector<node*>& frontier);