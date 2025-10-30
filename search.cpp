#include "class.h"
#include <iostream>
#include <queue>


int misplaced(const state&);
float euclidean(const state&);

node* SEARCH(const Problem& p, int* expand_num, int* max_queue_num){
    /*node* (*method_array[3])(std::priority_queue<node*, std::vector<node*>, cost_compare>&) = {
        uniform_cost,
        Astar_misplaced,
        Astar_Euclidean
    };
    auto method = method_array[p.method];*/
    node* initial = new node(p.initial, nullptr);
    if(p.method == 1)
        initial->st.distance = misplaced(initial->st);
    if(p.method == 2)
        initial->st.distance = euclidean(initial->st);
    
    std::priority_queue<node*, std::vector<node*>, cost_compare>frontier;
    frontier.push(initial);
    std::unordered_set<std::string> explored;
    node* chosen = nullptr;
    *expand_num = 0;
    *max_queue_num = 1;
    std::cout << std::endl << "Initial state:" << std::endl;
    initial->print();

    while(1){
        if (frontier.empty()){
            std::cout << "No solution!" << std::endl;
            return nullptr;
        }
        if(frontier.size() > *max_queue_num)
            *max_queue_num = frontier.size();
        chosen = frontier.top();
        frontier.pop();
        if(explored.count(chosen->st.label))
            continue;
        explored.insert(chosen->st.label);
        std::cout << "The best state to expand with g(n) = " << chosen->st.cost
        << " and h(n) = " << chosen->st.distance << " is:" << std::endl;
        chosen->print();
        if(chosen->st == p.goal){
            std::cout << "Goal!" << std::endl;
            return chosen;
        }
        else{
            std::cout << "Expanding this state..." << std::endl;
            chosen->expand(frontier, explored, p.method);
            *expand_num += 1;
        }
    }
}
