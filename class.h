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

    bool operator==(const state& other){ // for end state check
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                if(this->position[i][j] != other.position[i][j])
                    return false;
        return true;
    }

    bool operator!=(const state& other){
        return !(*this == other);
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