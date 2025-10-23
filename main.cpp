#include "class.h"
#include "func.h"
#include <iostream>

node* SEARCH(Problem p){
    node* (*method_array[3])(std::vector<node*>&) = {
        uniform_cost,
        Astar_misplaced,
        Astar_Euclidean
    };
    auto method = method_array[p.method];
    node* initial = new node(p.initial, nullptr);
    std::vector<node*> frontier = {initial};
    std::unordered_set<std::string> explored;
    node* chosen = nullptr;

    while(1){
        if (frontier.empty()){
            std::cout << "No solution found!" << std::endl;
            return nullptr;
        }
        chosen = method(frontier);
        if(chosen->st == p.goal)
            return chosen;
        else
            chosen->expand(&frontier, &explored);
    }
}
