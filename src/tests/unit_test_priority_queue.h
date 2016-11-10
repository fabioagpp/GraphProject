#include <iostream>
#include <stdlib.h>
#include "../graph.h"

using namespace std;

bool test_heap_node_constructor(){
    heap_node *h1 = new heap_node(1, 0.5);

    cout << "Testing the heap_node's constructor... ";

    if(h1->id != 1){
        cout << "Error: h1->id (" << h1->id;
        cout << ") does not match the expected(1)." << endl;
        return false;
    }   

    if(h1->weight != 0.5){
        cout << "Error: h1->weight (" << h1->weight;
        cout << ") does not match the expected(0.5)." << endl;
        return false;
    }   

    delete h1;

    cout << "Test Successful" << endl;
    return true;
}

bool test_priority_queue_push(){
    cout << "Testing the Priority_Queue's push function... ";
    Priority_Queue *q = new Priority_Queue(10);
    vector<int> expected_values = {1, 2, 3};
    vector<int> *obtained_values;
    q->push(1, 3);
    q->push(2, 4);
    q->push(3, 5);
    
    obtained_values = q->get_order();

    if(expected_values != *obtained_values){
        cout << "Error: The obtained index order(";
        for(int i = 0; i < obtained_values->size(); i++){
            cout << obtained_values->at(i) << ", ";
        }
        cout << ") for the first 3 pushes is different from the expected(";
        for(int i = 0; i < expected_values.size(); i++){
            cout << expected_values.at(i) << ", ";
        }
        cout << ")." << endl;
        return false;
    }
    
    expected_values = {1, 2, 3, 4};
    q->push(4, 6);
    obtained_values = q->get_order();

    if(expected_values != *obtained_values){
        cout << "Error: The obtained index order(";
        for(int i = 0; i < obtained_values->size(); i++){
            cout << obtained_values->at(i) << ", ";
        }
        cout << ") for the fourth push is different from the expected(";
        for(int i = 0; i < expected_values.size(); i++){
            cout << expected_values.at(i) << ", ";
        }
        cout << ")." << endl;
        return false;
    }
    
    expected_values = {5, 1, 3, 4, 2};
    q->push(5, 1);
    obtained_values = q->get_order();

    if(expected_values != *obtained_values){
        cout << "Error: The obtained index order(";
        for(int i = 0; i < obtained_values->size(); i++){
            cout << obtained_values->at(i) << ", ";
        }
        cout << ") for the fifth push is different from the expected(";
        for(int i = 0; i < expected_values.size(); i++){
            cout << expected_values.at(i) << ", ";
        }
        cout << ")." << endl;
        return false;
    }
    delete q;
    cout << "Test Successful" << endl;
    return true;
}

bool test_priority_queue_pop(){
    cout << "Testing the Priority_Queue's pop function... ";
    Priority_Queue *q = new Priority_Queue(10);
    vector<int> expected_values = {1, 2, 3};
    vector<int> *obtained_values;
    q->push(1, 3);
    q->push(2, 4);
    q->push(3, 5);
    
    obtained_values = new vector<int>;

    obtained_values->push_back(q->pop()->id);
    obtained_values->push_back(q->pop()->id);
    obtained_values->push_back(q->pop()->id);

    if(expected_values != *obtained_values){
        cout << "Error: The obtained index order(";
        for(int i = 0; i < obtained_values->size(); i++){
            cout << obtained_values->at(i) << ", ";
        }
        cout << ") for the pops is different from the expected(";
        for(int i = 0; i < expected_values.size(); i++){
            cout << expected_values.at(i) << ", ";
        }
        cout << ")." << endl;
        return false;
    }

    delete q;
    cout << "Test Successful" << endl;
    return true;
}

bool test_priority_queue_update(){
    cout << "Testing the Priority_Queue's update function... ";
    Priority_Queue *q = new Priority_Queue(10);
    vector<int> expected_values = {1, 4, 3, 2};
    vector<int> *obtained_values;
    q->push(1, 3);
    q->push(2, 4);
    q->push(3, 5);
    q->push(4, 6);
    q->update(4, 3.5);

    obtained_values = q->get_order();
    

    if(expected_values != *obtained_values){
        cout << "Error: The obtained index order(";
        for(int i = 0; i < obtained_values->size(); i++){
            cout << obtained_values->at(i) << ", ";
        }
        cout << ") for the first update is different from the expected(";
        for(int i = 0; i < expected_values.size(); i++){
            cout << expected_values.at(i) << ", ";
        }
        cout << ")." << endl;
        return false;
    }

    q->update(4, 2);

    expected_values = {4, 1, 3, 2};

    obtained_values = q->get_order();
    

    if(expected_values != *obtained_values){
        cout << "Error: The obtained index order(";
        for(int i = 0; i < obtained_values->size(); i++){
            cout << obtained_values->at(i) << ", ";
        }
        cout << ") for the second update is different from the expected(";
        for(int i = 0; i < expected_values.size(); i++){
            cout << expected_values.at(i) << ", ";
        }
        cout << ")." << endl;
        return false;
    }

    q->update(2, 1);

    expected_values = {2, 4, 3, 1};

    obtained_values = q->get_order();
    

    if(expected_values != *obtained_values){
        cout << "Error: The obtained index order(";
        for(int i = 0; i < obtained_values->size(); i++){
            cout << obtained_values->at(i) << ", ";
        }
        cout << ") for the third update is different from the expected(";
        for(int i = 0; i < expected_values.size(); i++){
            cout << expected_values.at(i) << ", ";
        }
        cout << ")." << endl;
        return false;
    }

    delete q;
    cout << "Test Successful" << endl;
    return true;
}
