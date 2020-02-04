//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"

#include <stdio.h>
#include <queue>
#include <list>
#include <map>

#define MAX_DEPTH 40

State *goal_state;
State *initial_state;
std::map <long long int, bool> forward_m;
std::map <long long int, bool> backward_m;
int node_expanded;
bool is_found;

void run_dls_backward(Node *current_node) {
    //printf("current node depth: %d\n", current_node->depth);
    //printf("board_key: %lld\n", construct_board_key(current_node->state));
    //print_board(current_node->state);

    if(current_node->depth > MAX_DEPTH) return;

    long long int current_state_key = construct_board_key(current_node->state);
    if(forward_m.find(current_state_key) != forward_m.end()) {
        printf("[%s] found solution by expending [%d] nodes\n", __func__, node_expanded);
        is_found = true;
        return;
    }
    std::list<Node *> child_list = expand_node(current_node, goal_state);
    node_expanded += 1;
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(backward_m.find(child_state_key) == backward_m.end()) {
            backward_m[child_state_key] = true;
            run_dls_backward(*it);
            if(is_found) return;
        }
    }
}

void run_dls_forward(Node *current_node) {
    //printf("current node depth: %d\n", current_node->depth);
    //printf("board_key: %lld\n", construct_board_key(current_node->state));
    //print_board(current_node->state);

    if(current_node->depth > MAX_DEPTH) return;

    if(equal_state(current_node->state, goal_state)) {
        printf("[%s] found solution by expending [%d] nodes\n", __func__, node_expanded);
        is_found = true;
        return;
    }
    std::list<Node *> child_list = expand_node(current_node, goal_state);
    node_expanded += 1;
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(forward_m.find(child_state_key) == forward_m.end()) {
            forward_m[child_state_key] = true;
            run_dls_forward(*it);
            if(is_found) return;
        }
    }
}

int main() {
    goal_state = construct_goal_state();
    initial_state = construct_initial_state();

    forward_m[construct_board_key(initial_state)] = true;
    backward_m[construct_board_key(goal_state)] = true;

    node_expanded = 0;
    is_found = false;

    run_dls_forward(create_new_node(0, calculate_manhattan_distance(initial_state, goal_state), NULL, initial_state));
    if(!is_found) {
        run_dls_backward(create_new_node(0, calculate_manhattan_distance(goal_state, initial_state), NULL, goal_state));
    }

    return 0;
}