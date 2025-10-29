#include "class.h"
#include "func.h"
#include <algorithm>
#include <limits>

node* uniform_cost(std::vector<node*>& frontier) {
    if (frontier.empty()) {
        return nullptr; // empty frontier case
    }

    // find the node with the smallest cost in frontier
    auto min = std::min_element(
        frontier.begin(),
        frontier.end(),
        [](const node* a, const node* b) {
            // compare the st.cost member of nodes
            return a->st.cost < b->st.cost;
        }
    );

    // get the node with the smallest cost and remove it from frontier
    node* chosen = *min;

    // remove the chosen node from the vector
    // first swap the smallest element with the last element
    std::iter_swap(min, frontier.end() - 1);
    // remove the last element
    frontier.pop_back();

    return chosen;
}

node* Astar_misplaced(std::vector<node*>& frontier){
    return nullptr;
}

node* Astar_Euclidean(std::vector<node*>& frontier){
    return nullptr;
}