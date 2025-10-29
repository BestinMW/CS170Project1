#include "class.h"
#include <iostream>
#include <queue>

node* SEARCH(const Problem& p){
    /*node* (*method_array[3])(std::priority_queue<node*, std::vector<node*>, cost_compare>&) = {
        uniform_cost,
        Astar_misplaced,
        Astar_Euclidean
    };
    auto method = method_array[p.method];*/
    node* initial = new node(p.initial, nullptr);
    std::priority_queue<node*, std::vector<node*>, cost_compare>frontier;
    frontier.push(initial);
    std::unordered_set<std::string> explored;
    explored.insert(initial->st.label);
    node* chosen = nullptr;

    while(1){
        if (frontier.empty()){
            std::cout << "No solution found!" << std::endl;
            return nullptr;
        }
        chosen = frontier.top();
        frontier.pop();
        if(chosen->st == p.goal)
            return chosen;
        else
            chosen->expand(frontier, explored, p.method);
    }
}
