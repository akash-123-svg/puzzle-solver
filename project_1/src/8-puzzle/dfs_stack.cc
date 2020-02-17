//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <stack>
#include <list>
#include <map>

class DfsStackEightPuzzle : public Solver {
public:
    DfsStackEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
        DfsStackEightPuzzle::init(_initial_state, _goal_state, _heuristic);
    }

    int init(State *_initial_state, State *_goal_state, Heuristic *_heuristic);

    int run();

    void destroy();

private:
    /* Private Data */
    State *goal_state;
    State *initial_state;
    Heuristic *heuristic;
    std::map<long long int, bool> m;
    int node_expanded;

    void run_dfs_stack();
};

int DfsStackEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    node_expanded = 0;

    return 1;
}

void DfsStackEightPuzzle::run_dfs_stack() {
    std::stack<Node *> s;
    s.push(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state));
    m[construct_board_key(initial_state)] = true;

    while(!s.empty()) {
        Node *current_node = s.top(); s.pop();

        //printf("current node depth: %d\n", current_node->depth);
        //printf("board_key: %lld\n", construct_board_key(current_node->state));
        //print_board(current_node->state);

        //if(node_expanded > 400) return;

        if(equal_state(current_node->state, goal_state)) {
            printf("found solution by expending [%d] nodes\n", node_expanded);
            break;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        node_expanded += 1;
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(m.find(child_state_key) == m.end()) {
                m[child_state_key] = true;
                s.push(*it);
            }
        }
    }
}

int DfsStackEightPuzzle::run() {
    run_dfs_stack();
    return 1;
}

void DfsStackEightPuzzle::destroy() {
    //
}