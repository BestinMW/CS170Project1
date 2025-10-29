#include "class.h"
#include "func.h"
#include <iostream>

using namespace std;

node* SEARCH(const Problem& p);
void backtraverse(node*);

int main(){
    int a, b, c;
    int p[3][3];
    int goal_p[3][3] = {1,2,3,4,5,6,7,8,0};
    for(int i = 0; i < 3; ++i){
        cin >> a >> b >> c;
        p[i][0] = a;
        p[i][1] = b;
        p[i][2] = c;
    }
    state initial(p);
    state goal(goal_p);
    Problem pr(initial,goal,0);
    node* answer = SEARCH(pr);
    if(answer != nullptr)
        backtraverse(answer);
    else
        cout << "no solution!";
    return 0;
}