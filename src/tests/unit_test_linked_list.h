#include <iostream>
#include <stdlib.h>
#include "../graph.h"

bool test_list_node_constructor(){
    list_node *l1 = new list_node(5);
    list_node *l2 = new list_node(7);
    list_node *l3 = new list_node(6, l2, l1);

    cout << "Testing the list_node's constructor... ";

    if(l1->next != l3){
        cout << "Error: l1->next does not match." << endl;
        return false;
    }   
    if(l2->previous != l3){
        cout << "Error: l2->previous does not match." << endl;
        return false;
    }   
    if(l3->next != l2){
        cout << "Error: l3->next does not match." << endl;
        return false;
    }   
    if(l3->previous != l1){
        cout << "Error: l3->previous does not match." << endl;
        return false;
    }   
    cout << "Test Successful" << endl;
    return true;
}

bool test_list_node_destructor(){
    list_node *l1 = new list_node(5);
    list_node *l2 = new list_node(7);
    list_node *l3 = new list_node(6, l2, l1);
    delete l3; 

    cout << "Testing the list_node's destructor... ";

    if(l1->next != l2){
        cout << "Error: l1->next does not match." << endl;
        return false;
    }   
    if(l2->previous != l1){
        cout << "Error: l2->previous does not match." << endl;
        return false;
    }   
    cout << "Test Successful" << endl;
    return true;
}

bool test_linked_list_push(){
    Linked_List *l = new Linked_List;

    cout << "Testing the Linked_List's push function... ";

    int push_val1 = 5;
    l->push(push_val1);
    if(l->head == NULL or l->head->edge != push_val1){
        cout << "Error: list's head value does not match the one from the first push." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val1){
        cout << "Error: list's tail value does not match the one from the first push." << endl;
        return false;
    }
    int push_val2 = 3;
    l->push(push_val2);
    if(l->head == NULL or l->head->edge != push_val2){
        cout << "Error: list's head value does not match the one from the second push." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val1){
        cout << "Error: list's tail value does not match the one from the second push." << endl;
        return false;
    }
    cout << "Test Successful" << endl;
    delete l;
    return true;
}

bool test_linked_list_push_ordered(){
    Linked_List *l = new Linked_List;

    cout << "Testing the Linked_List's push_ordered function... ";

    int push_val1 = 5;
    l->push_ordered(push_val1);
    if(l->head == NULL or l->head->edge != push_val1){
        cout << "Error: list's head value does not match the one from the first push." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val1){
        cout << "Error: list's tail value does not match the one from the first push." << endl;
        return false;
    }
    int push_val2 = 3;
    l->push_ordered(push_val2);
    if(l->head == NULL or l->head->edge != push_val2){
        cout << "Error: list's head value does not match the one from the second push." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val1){
        cout << "Error: list's tail value does not match the one from the second push." << endl;
        return false;
    }
    int push_val3 = 7;
    l->push_ordered(push_val3);
    if(l->head == NULL or l->head->edge != push_val2){
        cout << "Error: list's head value does not match the one from the third push." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val3){
        cout << "Error: list's tail value does not match the one from the third push." << endl;
        return false;
    }
    cout << "Test Successful" << endl;
    delete l;
    return true;
}

bool test_linked_list_push_back(){
    Linked_List *l = new Linked_List;

    cout << "Testing the Linked_List's push_back function... ";

    int push_val1 = 5;
    l->push_back(push_val1);
    if(l->head == NULL or l->head->edge != push_val1){
        cout << "Error: list's head value does not match the one from the first push." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val1){
        cout << "Error: list's tail value does not match the one from the first push." << endl;
        return false;
    }
    int push_val2 = 3;
    l->push_back(push_val2);
    if(l->head == NULL or l->head->edge != push_val1){
        cout << "Error: list's head value does not match the one from the second push." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val2){
        cout << "Error: list's tail value does not match the one from the second push." << endl;
        return false;
    }
    cout << "Test Successful" << endl;
    delete l;
    return true;
}

bool test_linked_list_pop(){
    Linked_List *l = new Linked_List;

    cout << "Testing the Linked_List's pop function... ";

    int pop_val = l->pop();
    if(l->head != NULL){
        cout << "Error: list's head value does not match the one from the first pop." << endl;
        return false;
    }
    if(l->tail != NULL){
        cout << "Error: list's tail value does not match the one from the first pop." << endl;
        return false;
    }
    if(pop_val != 0){
        cout << "Error: return value does not match the one from the first pop." << endl;
        return false;
    }

    int push_val1 = 5;
    int push_val2 = 3;
    int push_val3 = 1;
    l->push(push_val1);
    l->push(push_val2);
    l->push(push_val3);
    pop_val = l->pop();
    if(l->head == NULL or l->head->edge != push_val2){
        cout << "Error: list's head value does not match the one from the second pop." << endl;
        return false;
    }
    if(l->tail == NULL or l->tail->edge != push_val1){
        cout << "Error: list's tail value does not match the one from the second pop." << endl;
        return false;
    }
    if(pop_val != push_val3){
        cout << "Error: return value does not match the one from the second pop." << endl;
        return false;
    }

    pop_val = l->pop();
    pop_val = l->pop();
    if(l->head != NULL){
        cout << "Error: list's head value does not match the one from the third pop." << endl;
        return false;
    }
    if(l->tail != NULL){
        cout << "Error: list's tail value does not match the one from the third pop." << endl;
        return false;
    }
    if(pop_val != push_val1){
        cout << "Error: return value does not match the one from the third pop." << endl;
        return false;
    }

    cout << "Test Successful" << endl;
    delete l;
    return true;
}


