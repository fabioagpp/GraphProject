
using namespace std;

class list_node {
    public:
        int edge;
        float weight;
        list_node *next;
        list_node *previous;

        list_node(int edge, list_node *next = NULL,
                list_node *previous = NULL, float weight = 1){
            this->edge = edge;
            this->weight = weight;
            this->next = next;
            this->previous = previous;

            if(next != NULL)
                next->previous = this;
            if(previous != NULL)
                previous->next = this;
        }
        ~list_node(){
            if(previous != NULL){
                previous->next = next;
            }
            if(next != NULL){
                next->previous = previous;
            }
        }
};

class Linked_List{
    public:
        list_node *head;
        list_node *tail;

        Linked_List(){
            head = NULL;
            tail = NULL;
        }

        ~Linked_List(){
            while(pop() != 0){
                continue;
            }
        }

        void push(int edge, float weight = 1){
            if(head == NULL){
                head = new list_node(edge, NULL, NULL, weight);
                tail = this->head;
            }else{
                head = new list_node(edge, head, NULL, weight);
            }
        }

        void push_ordered(int edge, float weight = 1){
            if(head == NULL or head->edge > edge){
                push(edge, weight);
                return;
            }
            list_node *before = head;
            list_node *after = head->next;

            while(after != NULL and after->edge < edge){
                before = after;
                after = after->next;
            }

            new list_node(edge, after, before, weight);

            if(before == tail){
                tail = tail->next;
            }
        }

        void push_back(int edge, float weight = 1){
            if(tail == NULL){
                push(edge, weight);
            }else{
                tail = new list_node(edge, NULL, tail, weight);
            }
        }

        list_node *find(int edge){
            list_node *l = head;
            while(l != NULL and l->edge != edge){
                l = l->next;
            }

            return l;
        }

        int pop(){
            if(head == NULL){
                return 0;
            }

            if(tail == head){
                tail = NULL;
            }

            int i = head->edge;
            list_node *l = head;
            head = head->next;
            delete l;
            return i;
        }

        void print(){
            list_node *l = head;
            while(l->next != NULL){
                cout << l->edge << ", ";
                l = l->next;
            }
            cout << l->edge << endl;
        }
        
        void delete_node(list_node *l){
            if(l == head)
                head = l->next;
            if(l == tail)
                tail = l->previous;
            delete l;
        }
};
