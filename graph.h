#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "linked_list.h"

using namespace std;

class Graph{
    protected:
        int size;
        class neighborsIter{
            public:
                virtual int end() = 0;
                virtual int begin() = 0;
                virtual int next() = 0;
                virtual int previous() = 0;
        };
    public:
        int *degree;
        int *latest_search_parent;
        int *latest_search_depth;
        vector<vector<int> > *components;
        virtual void iterate_neighbors(int vertex, bool reverse=false) = 0;
        virtual bool is_neighbor(int head, int tail) = 0;
        virtual void set_graph_size(int size){
            this->size = size;
            degree = new int[size];
            fill_n(degree, size, 0);
        }
        virtual void add_edge(int head, int tail){
            degree[head-1]++;
            degree[tail-1]++;
        };

        neighborsIter *iterator;

        Graph(){
            degree = NULL;
            latest_search_parent = NULL;
            latest_search_depth = NULL;
            components = NULL;
            iterator = NULL;
        }

        virtual ~Graph(){
            if(iterator != NULL)
                delete iterator;
            if(latest_search_parent != NULL)
                delete latest_search_parent;
            if(latest_search_depth != NULL)
                delete latest_search_depth;
            if(degree != NULL)
                delete degree;
        }
        int get_size(){
            return size;
        }
        
        void read_file(string filename){
            string s1;
            string s2;
            int i1;
            int i2;
            string line;

            ifstream input(filename.c_str());
            getline(input, line);
            sscanf(line.c_str(), "%d", &i1);
            set_graph_size(i1);

            while(getline(input, line)){
                stringstream line_stream(line);
                getline(line_stream, s1, ' ');
                sscanf(s1.c_str(), "%d", &i1);
                getline(line_stream, s2, ' ');
                sscanf(s2.c_str(), "%d", &i2);
                add_edge(i1, i2);
            }
            input.close();
        }

        void generate_info(string filename="graph_info.txt"){
            int n = size;
            int m = 0;
            double *degree_distribution = new double[n];
            fill_n(degree_distribution, size, 0);


            int i;
            for(i = 0; i < size; i++){
                m += degree[i];
                degree_distribution[degree[i]]++;
            }

            ofstream output(filename.c_str());
            output << "# n = " << n << endl;
            output << "# m = " << m/2 << endl;
            output << "# d_medio = " << double(m)/double(n) << endl;
            
            int first_zero;
            bool printed_zero_range = true;
            for(i = 0; i < size; i++){
                if(degree_distribution[i] == 0){
                    if(printed_zero_range){
                        first_zero = i;
                        printed_zero_range = false;
                    }
                }
                else{
                    if(!printed_zero_range){
                        printed_zero_range = true;
                        for(int j = first_zero; j < i; j++){
                            output << j << " " << degree_distribution[j]/double(n) << endl;
                        }
                    }
                    output << i << " " << degree_distribution[i]/double(n) << endl;
                }
            }

            delete degree_distribution;

        }

        void reset_search(){
            if(latest_search_parent != NULL)
                delete latest_search_parent;
            if(latest_search_depth != NULL)
                delete latest_search_depth;

            latest_search_parent = new int[size];
            fill_n(latest_search_parent, size, -1); 
            latest_search_depth = new int[size];
            fill_n(latest_search_depth, size, -1); 


        }

        void generate_bfs_tree(int root, string filename="bfs.txt"){
            reset_search();
            int *parent = latest_search_parent;
            int *depth = latest_search_depth;
            int u, v;
            Linked_List *l = new Linked_List;

            parent[root-1] = 0;
            depth[root-1] = 0;
            l->push(root);

            while(l->head != NULL){
                v = l->pop();
                
                iterate_neighbors(v);
                for(u=iterator->begin(); u<=iterator->end(); u=iterator->next()){
                    if(parent[u-1] == -1){
                        parent[u-1] = v;
                        depth[u-1] = depth[v-1] + 1;
                        l->push_back(u);
                    }
                }
            }

            if(filename != "void"){
                write_search(filename);
            }
            
            delete l;
        }

        void write_search(string filename){
            int *parent = latest_search_parent;
            int *depth = latest_search_depth;

            ofstream output(filename.c_str());
            output << "vertex,parent,depth\n";

            for(int i = 0; i < size; i++){
                if(parent[i] != -1){
                    output << i+1 << "," << parent[i] << "," << depth[i] << "\n";
                }
            }
            output.close();
        }

        void generate_dfs_tree(int root, string filename="dfs.txt"){
            reset_search();
            bool markup[size] = {false};
            int *parent = latest_search_parent;
            int *depth = latest_search_depth;
 
            int u, v;
            Linked_List *l = new Linked_List;

            parent[root-1] = 0;
            depth[root-1] = 0;
            l->push(root);

            while(l->head != NULL){
                v = l->pop();
                if(markup[v-1] == true){
                    continue;
                }

                markup[v-1] = true;
                
                iterate_neighbors(v, true);
                for(u=iterator->end(); u>=iterator->begin(); u=iterator->previous()){
                    if(markup[u-1] == false){
                        parent[u-1] = v;
                        depth[u-1] = depth[v-1] + 1;
                        l->push(u);
                    }
                }
            }
            
            if(filename != "void"){
                write_search(filename);
            }

            delete l;
        }

        void generate_connected_components(string filename="cc.txt"){
            if(components != NULL){
                delete components;
            }
            components = new vector<vector<int> >;
            vector<int> *cc;

            // Unexplored vertices pool.
            list_node **list_access = new list_node*[size];
            Linked_List *remaining_vertices = new Linked_List;
            for(int i = 0; i < size; i++){
                remaining_vertices->push(i+1);
                list_access[i] = remaining_vertices->head;
            }

            // Loop of BFSs
            int root, u, v;
            Linked_List l;

            while(remaining_vertices->head != NULL){
                // Selects the root for a new connected component.
                root = remaining_vertices->pop();
                list_access[root-1] = NULL;

                cc = new vector<int>;
                cc->push_back(root);
                l.push(root);
                while(l.head != NULL){
                    v = l.pop();
                    
                    // Iterates through all the vertices neighbors
                    // and adds the unknown to the list.
                    iterate_neighbors(v);
                    for(u=iterator->begin(); u<=iterator->end(); u=iterator->next()){
                        if(list_access[u-1] != NULL){
                            l.push_back(u);
                            cc->push_back(u);
                            remaining_vertices->delete_node(list_access[u-1]);
                            list_access[u-1] = NULL;
                        }
                    }
                }

                components->push_back(*cc);
            }
            
            // Sorts the components by decreasing size.
            sort(components->begin(), components->end(),
                      [](vector<int> a, vector<int> b) {
                        return a.size() > b.size();
                        });

            // Writes to file.
            if(filename != "void"){
                ofstream output(filename.c_str());
                output << get_components_string();
            }

            delete list_access;
            

        }

        string get_components_string(){
            if(components == NULL)
                return "";

            stringstream output;
            output << "# n_componentes = " << components->size() << endl;
            int k = 1;
            for(vector<vector<int> >::iterator i = components->begin();
                                        i != components->end(); i++){
                output << "\n==========================\n";
                output << "# componente " << k << ":\n";
                output << "==========================\n\n";
                output << "# tamanho = " << i->size() << endl;
                output << "# vertices =";
                sort(i->begin(), i->end());
                for(vector<int>::iterator j = i->begin(); j != i->end(); j++){
                    output << " " << *j;
                }
                output << endl;
                
                k++;

            }
            
            return output.str();
        }

        int get_diameter(){
            int diameter = 0;
            int farthest_vertex = 1;
            generate_bfs_tree(1);
            for(int i = 0; i < size; i++){
                if(latest_search_depth[i] == -1)
                    return -1;
                else if(latest_search_depth[i] > diameter){
                    diameter = latest_search_depth[i];
                    farthest_vertex = i + 1;
                }

            }

            diameter = 0;
            generate_bfs_tree(farthest_vertex);
            for(int i = 0; i < size; i++){
                diameter = max(diameter, latest_search_depth[i]);
            }

            return diameter;
        }

};

class AdjacencyMatrixGraph: public Graph{
    protected:
        class neighborsIter : public Graph::neighborsIter{
            int vertex;
            int last;
            int first;
            int current;
            AdjacencyMatrixGraph *outer;
            public:
                neighborsIter(AdjacencyMatrixGraph *outer, int vertex, bool reverse=false){
                    this->vertex = vertex;
                    this->outer = outer;
                    int i = 0;
                    while(i < outer->size and outer->neighbors[vertex-1][i] != true){
                        i++;
                    }
                    first = i + 1;

                    i = outer->size - 1;
                    while(i >= 0 and outer->neighbors[vertex-1][i] != true){
                        i--;
                    }
                    last = i + 1;

                    if(reverse)
                        current = last;
                    else
                        current = first;
                }

                int begin(){
                    return first;
                }

                int end(){
                    return last;
                }
                
                int next(){
                    int i = current;
                    while(i <= last and outer->neighbors[vertex-1][i] == false){
                        i++;
                    }

                    current = i + 1;
                    return current;
                }
                
                int previous(){
                    int i = current - 2;
                    while(i >= first and outer->neighbors[vertex-1][i] == false){
                        i--;
                    }

                    current = i + 1;
                    return current;

                }
        };

    public:
        bool **neighbors;

        void set_graph_size(int size){
            Graph::set_graph_size(size);
            neighbors = new bool*[size];
            for(int i = 0; i < size; i++){
                neighbors[i] = new bool[size];
                for(int j = 0; j < size; j++){
                    neighbors[i][j] = 0;
                }
            }
        }

        void add_edge(int head, int tail){
            Graph::add_edge(head, tail);
            neighbors[head-1][tail-1] = true;
            neighbors[tail-1][head-1] = true;
        }

        bool is_neighbor(int head, int tail){
            return neighbors[head-1][tail-1];
        }

        void iterate_neighbors(int vertex, bool reverse=false){
            if(iterator != NULL){
                delete iterator;
            }
            iterator = new neighborsIter(this, vertex, reverse);
        }

        ~AdjacencyMatrixGraph(){
            if(neighbors != NULL){
                for(int i = 0; i < size; i++)
                    delete neighbors[i];
                delete neighbors;
            }
        }
};

class AdjacencyListGraph: public Graph{
   protected:
        class neighborsIter: public Graph::neighborsIter{
            private:
                list_node *first;
                list_node *last;
                list_node *current;
                AdjacencyListGraph *outer;
            public:
                neighborsIter(AdjacencyListGraph *outer, int vertex, bool reverse=false){
                    this->outer = outer;
                    first = outer->neighbors[vertex-1].head;
                    last = outer->neighbors[vertex-1].tail;
                    if(reverse)
                        current = last;
                    else
                        current = first;
                }
                
                int end(){
                    if(last == NULL){
                        return 0;
                    }
                    return last->edge;
                };
                int begin(){
                    if(first == NULL){
                        return outer->size + 1;
                    }
                    return first->edge;
                }
                int next(){
                    current = current->next;
                    if(current != NULL){
                        return current->edge;
                    }
                    else
                        return outer->size + 1;
                }
                int previous(){
                    current = current->previous;
                    if(current != NULL)
                        return current->edge;
                    else
                        return 0;
                }
        };
    public:
        Linked_List *neighbors;
        void iterate_neighbors(int vertex, bool reverse=false){
            if(iterator != NULL){
                delete iterator;
            }
            iterator = new neighborsIter(this, vertex, reverse);
        }
        void add_edge(int head, int tail){
            Graph::add_edge(head, tail);
            neighbors[head-1].push_ordered(tail);
            neighbors[tail-1].push_ordered(head);
        }
        bool is_neighbor(int head, int tail){
            return neighbors[head-1].find(tail) != NULL;
        }

        void set_graph_size(int size){
            Graph::set_graph_size(size);
            neighbors = new Linked_List[size];
        }

/*        ~AdjacencyListGraph(){
            if(neighbors != NULL)
                delete neighbors;
        }*/
};
