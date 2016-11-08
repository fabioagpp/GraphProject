#include <iostream>
#include <stdlib.h>
#include "unit_test_linked_list.h"
#include "unit_test_adjacency_list_graph.h"
#include "unit_test_adjacency_matrix_graph.h"

void execute_test(bool (*f) (void)){
    if(f() == false)
        exit(EXIT_FAILURE);
}
int main(){
    // List Node tests
    execute_test(test_list_node_constructor);
    execute_test(test_list_node_destructor);

    // Linked List tests
    execute_test(test_linked_list_push);
    execute_test(test_linked_list_push_ordered);
    execute_test(test_linked_list_push_back);
    execute_test(test_linked_list_pop);

    // Adjacency List Graph iterator tests
    execute_test(test_adjacency_list_graph_iterator_constructor);
    execute_test(test_adjacency_list_graph_iterator_next);
    execute_test(test_adjacency_list_graph_iterator_previous);
    execute_test(test_adjacency_list_graph_get_weight_forward);
    execute_test(test_adjacency_list_graph_get_weight_backward);

    // Adjacency Matrix Graph iterator tests
    execute_test(test_adjacency_matrix_graph_iterator_constructor);
    execute_test(test_adjacency_matrix_graph_iterator_next);
    execute_test(test_adjacency_matrix_graph_iterator_previous);
    execute_test(test_adjacency_matrix_graph_get_weight_forward);
    execute_test(test_adjacency_matrix_graph_get_weight_backward);

    return 0;
}
