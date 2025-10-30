#include "class.h"
#include <iostream>
#include <string>

using namespace std;

node* SEARCH(const Problem&, int*, int*);
void backtraverse(node*);

int main(){
    int a, b, c, x;
    int p[3][3];
    int goal_p[3][3] = {1,2,3,4,5,6,7,8,0};
    int expand_num;
    int max_queue_num;

    cout << "Welcome to LBY 8-puzzle solver!" << endl;
    cout << "Project collaborators: Jiahan Li, Bestin Watts, Yangao Yi" << endl;
    cout << "Enter your puzzle, use 0 for the blank" << endl;
    string rows[] = {"first", "second", "third"};
    for(int i = 0; i < 3; ++i){
        cout << "Enter the " << rows[i] << " row, use space or tabs between numbers: ";
        cin >> a >> b >> c;
        p[i][0] = a;
        p[i][1] = b;
        p[i][2] = c;
    }
    cout << endl << "Enter your choice of algorithms:" << endl;
    cout << "0: Uniform Cost Search" << endl;
    cout << "1: A* with the Misplaced Tile heuristic" << endl;
    cout << "2: A* with the Euclidean distance heuristic" << endl;
    cin >> x; //method
    state initial(p);
    state goal(goal_p);
    Problem pr(initial,goal,x);
    node* answer = SEARCH(pr, &expand_num, &max_queue_num);
    /*if(answer != nullptr)
        backtraverse(answer);
    else
        cout << "no solution!";*/

    cout << "To solve this problem the search algorithm expanded a total of " << expand_num 
    << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << max_queue_num 
    << " ." << endl;
    if(answer != nullptr)
        cout << "The depth of the goal node was " << answer->st.cost << " ." << endl;
    return 0;
}