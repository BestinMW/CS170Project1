#include "class.h"

void node::expand(std::vector<node*>* frontier_pt, std::unordered_set<std::string>* explored_pt){
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
            std::swap(new_state.label[ix * 3 + iy + 1], new_state.label[(ix+dx[i]) * 3 + iy+dy[i] + 1]); // change the label
            pt  = new node(new_state, this); // parent node is this!!!!
            if (!explored_pt->count(pt->st.label))
                frontier_pt->push_back(pt);
            else
                delete pt;
        }
    }
}

void backtraverse(node* solution);