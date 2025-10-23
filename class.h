#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

class state{
public:
    int position[3][3];
    int blank_x;
    int blank_y;
    int cost;
    float distance;
    std::string label;

    state(int p[3][3], int c = 0, float d = -1){ // assignment construction func
        label = "";
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                position[i][j] = p[i][j];
                label += std::to_string(position[i][j]);
                if(position[i][j] == 0){
                    blank_x = i;
                    blank_y = j;
                }
            }
        }
        cost = c;
        distance = d;
    }

    state(const state& other){  // clone construction func
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                position[i][j] = other.position[i][j];
        cost = other.cost;
        distance = other.distance;
        label = other.label;
        blank_x = other.blank_x;
        blank_y = other.blank_y;
    }

    state& operator=(const state& other){
        if(this != &other){
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    position[i][j] = other.position[i][j];
            cost = other.cost;
            distance = other.distance;
            label = other.label;
            blank_x = other.blank_x;
            blank_y = other.blank_y;
        }
        return *this;
    }
};

class node{
public:
    state st;
    node* parent;
    void expand(std::vector<node*>* frontier_pt, std::unordered_set<std::string>* explored_pt);

    node(state s, node* p): st(s), parent(p) {} // assignment

    node(const node& other) : st(other.st), parent(other.parent) {}  // clone construction
};

class Problem{
public:
    state initial;
    state goal;
    int method;

    Problem(const state& i, const state& g, int m) : initial(i), goal(g), method(m) {
    }
};

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