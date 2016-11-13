#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class heap_node {
    public:
        float weight;
        int id;
        heap_node(int id, float weight){
            this->weight = weight;
            this->id = id;
        }
};

class Priority_Queue{
    private:
        
        heap_node **queue;
        int *access;

        int tail; // Last occupied position.

        int get_parent_index(int id){
            return access[id]/2;
        }

        heap_node *get_parent(int id){
            return queue[get_parent_index(id)];
        }

        int get_left_child_index(int id){
            return 2*access[id];
        }
        
        heap_node *get_left_child(int id){
            return queue[get_left_child_index(id)];
        }

        int get_right_child_index(int id){
            return 2*access[id] + 1;   
        }
        
        heap_node *get_right_child(int id){
            return queue[get_right_child_index(id)];
        }

        void heapify_up(int id){
            heap_node *parent = get_parent(id);
            if(parent != NULL and get_weight(id) < parent->weight){
                swap(id, parent->id);
                heapify_up(id);
            }
        }

        void heapify_down(int id){
            heap_node *left_child = get_left_child(id);
            if(left_child == NULL){
                return;
            }
            heap_node *right_child = get_right_child(id);
            heap_node *min_child;
            if(right_child == NULL){
                min_child = left_child;
            }
            else{
                min_child = min_node(left_child, right_child);
            }

            if(get_weight(id) > min_child->weight){
                if(min_child == left_child){
                }else{
                }
                swap(id, min_child->id);
                heapify_down(id);
            }

        }

        void swap(int id1, int id2){
            int index1 = access[id1];
            int index2 = access[id2];

            heap_node *stub = queue[index1];

            queue[index1] = queue[index2];
            queue[index2] = stub;

            access[id1] = index2;
            access[id2] = index1;
        }

        heap_node *min_node(heap_node *a, heap_node *b){
            if(a->weight < b->weight){
                return a;
            }
            return b;
        }

    public:

        Priority_Queue(int max_size){
            queue = new heap_node*[max_size + 1]();
            access = new int[max_size + 1]();
            tail = 0;
        }

        void push(int id, float weight){
            tail++;
            queue[tail] = new heap_node(id, weight);
            access[id] = tail;
            heapify_up(id);
        }

        heap_node *pop(){
            if(tail == 0){
                return NULL;
            }
            
            heap_node *pop_target = queue[1];

            if(pop_target != queue[tail]){
                swap(queue[1]->id, queue[tail]->id);
            }

            access[queue[tail]->id] = 0;
            queue[tail] = NULL;
            tail--;

            if(queue[1] != NULL){
                heapify_down(queue[1]->id);
            }
            
            return pop_target;
        }

        void update(int id, float weight){
            queue[access[id]]->weight = weight;

            heapify_up(id);
            heapify_down(id);
        }

        float get_weight(int id){
            return queue[access[id]]->weight;
        }

        ~Priority_Queue(){
            for(int i = 1; i <= tail; i++){
                delete queue[i];
            }

            delete queue;
            delete access;
        }

        vector<int> *get_order(){
            vector<int> *v = new vector<int>;
            for(int i = 1; i <= tail; i++){
                if(queue[i] != NULL)
                    v->push_back(queue[i]->id);
                else
                    v->push_back(0);
            }

            return v;
        }
};
