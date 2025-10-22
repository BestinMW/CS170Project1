#include <string>
#include <vector>
#include <unordered_set>

class state{
public:
    int position[3][3];
    int cost;
    float distance;
    std::string label;

    state(int p[3][3], int c = 0, float d = -1){ // assignment construction func
        label = "";
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j){
                position[i][j] = p[i][j];
                label += std::to_string(position[i][j]);
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
    }
};

class node{
public:
    state* st;
    node* parent;
    void expand(std::vector<node*>* frontier_pt, std::unordered_set<std::string>* explored_pt);

    node(state* s, node* p){ // assignment
        st = s;
        parent = p;
    }

    node(const node& other){  // clone construction
        if (other.st)
            st = new state(*other.st);
        else
            st = nullptr;
        parent = other.parent;
    }

    ~node(){  // destruction
        delete st;
    }
};

class Problem{
public:
    state initial;
    state goal;
    int method;

    Problem(const state& i, const state& g, int m) : initial(i), goal(g), method(m) {
    }
};