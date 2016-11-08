#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "../graph.h"


bool test_adjacency_list_graph_iterator_constructor(){
    Graph *g = new AdjacencyListGraph;
    g->read_file("test.txt");
    g->iterate_neighbors(1);

    cout << "Testing the AdjacencyListGraph iterator's constructor... ";

    if(g->iterator->begin() != 2){
        cout << "Error: the first neighbor should not be " << g->iterator->begin();
        cout << "." << endl;
        return false;
    }   
    
    if(g->iterator->end() != 4){
        cout << "Error: the last neighbor should not be " << g->iterator->end();
        cout << "." << endl;
        return false;
    }
    cout << "Test Successful" << endl;
    return true;
}

bool test_adjacency_list_graph_iterator_next(){
    Graph *g = new AdjacencyListGraph;
    g->read_file("test.txt");
    g->iterate_neighbors(1);
    vector<int> expected_values = {2, 3, 4};
    vector<int> obtained_values;
    int j = 0;
    
    cout << "Testing the AdjacencyListGraph iterator's next function... ";

    for(int i = g->iterator->begin(); i <= g->iterator->end(); i = g->iterator->next()){
        if(find(expected_values.begin(), expected_values.end(), i) == expected_values.end()){
            cout << "Error: the neighbor " << i << " isn't a valid neighbor." << endl;
            return false;
        }
        if(i != expected_values[j]){
            cout << "Error: the order of the neighbors isn't correct. ";
            cout << "Expecting " << expected_values[j] << ", got " << i << ".\n";
            return false;
        }
        obtained_values.push_back(i);
        j++;
    }

    for(int i = 0; i < expected_values.size(); i++){
        if(find(obtained_values.begin(), obtained_values.end(), expected_values[i])
                == obtained_values.end()){
            cout << "Error: the expected neighbor " << expected_values[i];
            cout << " wasn't found." << endl;
            return false;
        }
    }

    cout << "Test Successful" << endl;
    return true;
}

bool test_adjacency_list_graph_iterator_previous(){
    Graph *g = new AdjacencyListGraph;
    g->read_file("test.txt");
    g->iterate_neighbors(1, true);
    vector<int> expected_values = {4, 3, 2};
    vector<int> obtained_values;
    int j = 0;
    
    cout << "Testing the AdjacencyListGraph iterator's previous function... ";
    for(int i = g->iterator->end(); i >= g->iterator->begin(); i = g->iterator->previous()){
        if(find(expected_values.begin(), expected_values.end(), i) == expected_values.end()){
            cout << "Error: the neighbor " << i << " isn't a valid neighbor." << endl;
            return false;
        }
        if(i != expected_values[j]){
            cout << "Error: the order of the neighbors isn't correct. ";
            cout << "Expecting " << expected_values[j] << ", got " << i << ".\n";
            return false;
        }
        obtained_values.push_back(i);
        j++;
    }

    for(int i = 0; i < expected_values.size(); i++){
        if(find(obtained_values.begin(), obtained_values.end(), expected_values[i])
                == obtained_values.end()){
            cout << "Error: the expected neighbor " << expected_values[i];
            cout << " wasn't found." << endl;
            return false;
        }
    }

    cout << "Test Successful" << endl;
    return true;
}

bool test_adjacency_list_graph_get_weight_forward(){
        
    Graph *g = new AdjacencyListGraph(true);
    g->read_file("test.txt");
    g->iterate_neighbors(1);
    vector<float> expected_values = {2, 0.75, 2}; 
    float found_weight;
    int j = 0;
        
    cout << "Testing the AdjacencyListGraph iterator's get_weight function";
    cout << " in a forward iteration... ";

    for(int i = g->iterator->begin(); i <= g->iterator->end(); i = g->iterator->next()){
        found_weight = g->iterator->get_weight();
        if(found_weight != expected_values[j]){
            cout << "Error: The weight found(" << found_weight;
            cout << ") for the neighbor " << i;
            cout << " is different from the expected(" << expected_values[j];
            cout << ")." << endl;
            return false;
        }   
        j++;
    }

    cout << "Test Successful" << endl;
    return true;
}

bool test_adjacency_list_graph_get_weight_backward(){
        
    Graph *g = new AdjacencyListGraph(true);
    g->read_file("test.txt");
    g->iterate_neighbors(1, true);
    vector<float> expected_values = {2, 0.75, 2}; 
    float found_weight;
    int j = 0;
        
    cout << "Testing the AdjacencyListGraph iterator's get_weight function";
    cout << " in a forward iteration... ";

    for(int i = g->iterator->end(); i >= g->iterator->begin(); i = g->iterator->previous()){
        found_weight = g->iterator->get_weight();
        if(found_weight != expected_values[j]){
            cout << "Error: The weight found(" << found_weight;
            cout << ") for the neighbor " << i;
            cout << " is different from the expected(" << expected_values[j];
            cout << ")." << endl;
            return false;
        }   
        j++;
    }

    cout << "Test Successful" << endl;
    return true;
}
