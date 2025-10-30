#include "class.h"
#include <deque>
#include <iostream>
#include <cmath>

int misplaced(const state& s){
    int cnt = 0;
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j){
            if(s.position[i][j] != 0 && s.position[i][j] != i*3+j+1)
                cnt++;
        }
    return cnt;
}

float euclidean(const state& s){
    float total = 0;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if (s.position[i][j] != 0 && s.position[i][j] != i*3+j+1) {
                int goal_x = (s.position[i][j]-1)/3;
                int goal_y = (s.position[i][j]-1)%3;
                int x_diff = std::pow((goal_x - i),2);
                int y_diff = std::pow((goal_y - j),2);
                total += std::sqrt(x_diff+y_diff);

                // manhattan distance
                // int x_diff = std::abs(goal_x - i);
                // int y_diff = std::abs(goal_y - j);
                // total += x_diff+y_diff;
            }
        }
    }
    return total;
}

void node::expand(std::priority_queue<node*, std::vector<node*>, cost_compare>& frontier, std::unordered_set<std::string>& explored, int which_heuristic){
    int ix = this->st.blank_x;
    int iy = this->st.blank_y;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    node* pt;
    std::vector<node*> candidate;
    for(int i = 0; i < 4; ++i){
        if(ix+dx[i]>=0 && ix+dx[i]<=2 && iy+dy[i]>=0 && iy+dy[i]<=2){
            state new_state(this->st);
            std::swap(new_state.position[ix+dx[i]][iy+dy[i]], new_state.position[ix][iy]); // change position
            new_state.blank_x += dx[i]; // change blank_x
            new_state.blank_y += dy[i]; // change blank_y
            new_state.cost += 1; // add 1 to cost
            new_state.distance = -1; // reset the distance
            std::swap(new_state.label[ix * 3 + iy], new_state.label[(ix+dx[i]) * 3 + iy+dy[i]]); // change the label
            pt  = new node(new_state, this); // parent node is this!!!!

            if (!explored.count(pt->st.label)){
                if(which_heuristic == 1)
                    pt->st.distance = misplaced(pt->st);
                if(which_heuristic == 2)
                    pt->st.distance = euclidean(pt->st);
                frontier.push(pt);
            }
            else
                delete pt;
        }
    }
}

void backtraverse(node* solution){
    std::deque<node*> seq = {solution};
    node* pt = solution->parent;
    while(pt != nullptr){
        seq.push_front(pt);
        pt = pt->parent;
    }

    int ct = 0;
    for(node* a: seq){
        std::cout << "Step" << ct << ":" << std::endl;
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                std::cout << a->st.position[i][j] << " ";
            }
            std::cout << std::endl;
        }
        ct++;
    }
}