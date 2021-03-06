#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <ctime>
#include "linked_list.h"
#include "priority_queue.h"

using namespace std;

class Graph{
    protected:
        bool has_negative_weight;
        bool weighted;
        int size;
        class neighborsIter{
            public:
                virtual int end() = 0;
                virtual int begin() = 0;
                virtual int next() = 0;
                virtual int previous() = 0;
                virtual float get_weight() = 0;
        };
    public:
        int *degree;
        int *latest_search_parent;
        float *latest_search_depth;
        vector<vector<int> > *components;
        virtual void iterate_neighbors(int vertex, bool reverse=false) = 0;
        virtual bool is_neighbor(int head, int tail) = 0;
        virtual void set_graph_size(int size){
            this->size = size;
            degree = new int[size];
            fill_n(degree, size, 0);
            has_negative_weight = false;
        }
        virtual void add_edge(int head, int tail, float weight = 1){
            degree[head-1]++;
            degree[tail-1]++;
            if(weight <= 0){
                has_negative_weight = true;
            }
        };
        virtual float get_weight(int v1, int v2) = 0;

        neighborsIter *iterator;

        Graph(bool weighted = false){
            degree = NULL;
            latest_search_parent = NULL;
            latest_search_depth = NULL;
            components = NULL;
            iterator = NULL;
            this->weighted = weighted;
            has_negative_weight = false;
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
            string s3;
            int i1;
            int i2;
            float weight;
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
                if(weighted){
                    getline(line_stream, s3, ' ');
                    sscanf(s3.c_str(), "%f", &weight);
                    add_edge(i1, i2, weight);
                }else{
                    add_edge(i1, i2);
                }
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
            latest_search_depth = new float[size];
            fill_n(latest_search_depth, size, -1); 


        }

        void generate_bfs_tree(int root, string filename="bfs.txt"){
            reset_search();
            int u, v;
            Linked_List *l = new Linked_List;

            latest_search_parent[root-1] = 0;
            latest_search_depth[root-1] = 0;
            l->push(root);

            while(l->head != NULL){
                v = l->pop();
                
                iterate_neighbors(v);
                for(u=iterator->begin(); u<=iterator->end(); u=iterator->next()){
                    if(latest_search_parent[u-1] == -1){
                        latest_search_parent[u-1] = v;
                        latest_search_depth[u-1] = latest_search_depth[v-1] + 1;
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
            float *depth = latest_search_depth;

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
            float *depth = latest_search_depth;
 
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
                diameter = max(diameter, ((int)latest_search_depth[i]));
            }

            return diameter;
        }

        float get_distance(int a, int b){
            if(weighted){
                dijkstra(a, "void");
            }else{
                generate_bfs_tree(a, "void");
            }

            return latest_search_depth[b-1];
        }

        void dijkstra(int root, string filename="dijkstra.txt"){
            if(has_negative_weight){
                throw invalid_argument("Dijkstra's algorythm cannot handle negative weights.");
            }
            reset_search();
            int *parent = latest_search_parent;
            float *depth = latest_search_depth;
            int u, v;
            float v_distance;
            heap_node *stub;

            float infinite = numeric_limits<float>::max();

            Priority_Queue *q = new Priority_Queue(size);
            for(int i = 0; i < size; i++){
                q->push(i+1, infinite);
            }

            parent[root-1] = 0;
            q->update(root, 0);

            bool ended = false;
            while(not ended){
                stub = q->pop();
                if(stub == NULL){
                    ended = true;
                    break;
                }
                    
                v = stub->id;
                v_distance = stub->weight;
                depth[v-1] = v_distance;
                
                iterate_neighbors(v);
                for(u=iterator->begin(); u<=iterator->end(); u=iterator->next()){
                    if(depth[u-1] >= 0){
                        continue;
                    }
                    if(v_distance + iterator->get_weight() < q->get_weight(u)){
                        parent[u-1] = v;
                        q->update(u, v_distance + iterator->get_weight());
                    }
                }


                delete stub;
            }


            if(filename != "void"){
                write_search(filename);
            }

            
            delete q;
        }
        
        float mst(int root=1, string filename="mst.txt"){
            if(has_negative_weight){
                throw invalid_argument("Prim's algorythm cannot handle negative weights.");
            }
            reset_search();
            int *parent = latest_search_parent;
            float *depth = latest_search_depth;
            int u, v;
            float v_distance;
            heap_node *stub;
            float total_weight = 0;

            float infinite = numeric_limits<float>::max();
            Priority_Queue *q = new Priority_Queue(size);
            for(int i = 0; i < size; i++){
                q->push(i + 1, infinite);
            }

            parent[root-1] = 0;
            depth[root-1] = 0;

            q->update(root, 0);

            bool ended = false;
            while(not ended){
                stub = q->pop();
                if(stub == NULL){
                    ended = true;
                    break;
                }
                    
                v = stub->id;
                if(stub->weight == infinite){
                    parent[v-1] = 0;
                    depth[v-1] = 0;
                    total_weight += 0;
                }else{
                    depth[v-1] = stub->weight;
                    total_weight += stub->weight;
                }
                                
                iterate_neighbors(v);
                for(u=iterator->begin(); u<=iterator->end(); u=iterator->next()){
                    if(depth[u-1] > -1){
                        continue;
                    }
                    if(iterator->get_weight() < q->get_weight(u)){
                        parent[u-1] = v;
                        q->update(u, iterator->get_weight());
                    }
                }

                delete stub;
            }

            if(filename != "void"){
                write_search(filename);
            }
            
            delete q;

            return total_weight;
        }

        float get_average_distance(){
            float infinite = numeric_limits<float>::max();
            float average_distance = 0;
            float valid_pairs = 0;
            for(int i = 1; i < size; i++){
                dijkstra(i, "void");
                for(int j = i; j < size; j++){
                    if(latest_search_depth[j] > 0 and latest_search_depth[j] != infinite){
                        valid_pairs++;
                        average_distance += latest_search_depth[j];
                    }
                }
            }

            return average_distance/valid_pairs;
        }

        float tsp(int root=1, string filename="tsp.txt", double max_time=3600){
            clock_t begin_time, end_time;
            double elapsed_time;
            reset_search();
            int *next = latest_search_parent;
            float infinite = numeric_limits<float>::max();
            bool visited[size] = {false};
            int u, v;
            int min_neighbor;
            float min_neighbor_weight;
            v = root;
            visited[v] = true;
            float total_weight = 0;
            begin_time = clock();
            // Greedy heuristic that always selects the closest unvisited neighbor
            for(int i = 0; i < size - 1; i++){
                iterate_neighbors(v);
                min_neighbor_weight = infinite;

                for(u=iterator->begin(); u<=iterator->end(); u=iterator->next()){
                    if(!visited[u] and iterator->get_weight() < min_neighbor_weight){
                        min_neighbor = u;
                        min_neighbor_weight = iterator->get_weight();
                    }
                }
                next[v-1] = min_neighbor;

                visited[min_neighbor] = true;
                v = min_neighbor;
                total_weight += min_neighbor_weight;

            }
                    
            next[v-1] = root;
            total_weight += get_weight(v, root);

            // Just a log, you can ignore it
            if(filename != "void"){
                ofstream output(filename.c_str());
                output << "Unoptimized Total weight: " << total_weight << endl;
                output << "Unoptimized Path:" << endl;

                v = root;
                output << root;

                for(int i = 0; i < size; i++){
                    v = next[v-1];
                    output << " " << v;
                    
                }
                output << endl;
                output.close();
            }

            // Define elapsed time to avoid errors
            end_time = clock();
            elapsed_time = double(end_time - begin_time)/CLOCKS_PER_SEC;

            // Optimization part
            while(elapsed_time < max_time and optimize(root)){
                next = latest_search_parent;
                end_time = clock();
                elapsed_time = double(end_time - begin_time)/CLOCKS_PER_SEC;
            }

            // Determine new weight after optimization
            v = root;
            total_weight = 0;
            while(next[v-1] != root){
                total_weight += get_weight(v, next[v-1]);
                v = next[v-1];
            }
            total_weight += get_weight(v, next[v-1]);
            
            // Just a log, you can ignore it
            if(filename != "void"){
                ofstream output(filename.c_str(), std::ofstream::app);
                output << "Optimized Total weight: " << total_weight << endl;
                output << "Optimized Path:" << endl;

                v = root;
                output << root;

                for(int i = 0; i < size; i++){
                    v = next[v-1];
                    output << " " << v;
                    
                }
                output << endl;
                output.close();
            }

            return total_weight;
        }

        bool optimize(int root){
            bool changed = false;
            int *next = latest_search_parent;

            int *new_next = new int[size];
            int v1 = root;
            int v2;
            int v;

            float dist1, dist2;
            // Finds a "crossing path"            
            while(next[v1-1] != root and !changed){
                v2 = next[next[v1-1]-1];
                while(v2 != root and !changed){
                    dist1 = get_weight(v1, next[v1-1]) + get_weight(v2, next[v2-1]);
                    dist2 = get_weight(v1, v2) + get_weight(next[v1-1], next[v2-1]);
                    // Uncrosses it
                    if(dist1 > dist2){
                        v = root;
                        // Copy first part of the path
                        while(v != v1){
                            new_next[v-1] = next[v-1];
                            v = next[v-1];
                        }
                        
                        new_next[v1-1] = v2;
                        v = next[v-1];
                        // Reverse the second part of the path
                        while(v != v2){
                            new_next[next[v-1]-1] = v;
                            v = next[v-1];
                        }

                        v = next[v2-1];
                        // Copy last part of the path
                        while(v != root){
                            new_next[v-1] = next[v-1];
                            v = next[v-1];
                        }

                        new_next[next[v1-1]-1] = next[v2-1];
                        latest_search_parent = new_next;
                        
                        changed = true;
                    }
                    v2 = next[v2-1];
                }
                v1 = next[v1-1];
            }

            if(changed){
                delete next;
            }else{
                delete new_next;
            }

            return changed;

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
                    while(i < outer->size and outer->neighbors[vertex-1][i] == 0){
                        i++;
                    }
                    first = i + 1;

                    i = outer->size - 1;
                    while(i >= 0 and outer->neighbors[vertex-1][i] == 0){
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
                    while(i <= last and outer->neighbors[vertex-1][i] == 0){
                        i++;
                    }

                    current = i + 1;
                    return current;
                }
                
                int previous(){
                    int i = current - 2;
                    while(i >= first and outer->neighbors[vertex-1][i] == 0){
                        i--;
                    }

                    current = i + 1;
                    return current;

                }

                float get_weight(){
                    return outer->neighbors[vertex - 1][current - 1];
                }
        };

    public:
        float **neighbors;

        void set_graph_size(int size){
            Graph::set_graph_size(size);
            neighbors = new float*[size];
            for(int i = 0; i < size; i++){
                neighbors[i] = new float[size];
                for(int j = 0; j < size; j++){
                    neighbors[i][j] = 0;
                }
            }
        }

        void add_edge(int head, int tail, float weight = 1){
            Graph::add_edge(head, tail, weight);
            neighbors[head-1][tail-1] = weight;
            neighbors[tail-1][head-1] = weight;
        }

        bool is_neighbor(int head, int tail){
            return neighbors[head-1][tail-1] != 0;
        }

        void iterate_neighbors(int vertex, bool reverse=false){
            if(iterator != NULL){
                delete iterator;
            }
            iterator = new neighborsIter(this, vertex, reverse);
        }

        float get_weight(int v1, int v2){
            return neighbors[v1-1][v2-1];

        }

        AdjacencyMatrixGraph(bool weighted = false) : Graph(weighted){
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

                float get_weight(){
                    return current->weight;
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
        void add_edge(int head, int tail, float weight = 1){
            Graph::add_edge(head, tail, weight);
            neighbors[head-1].push_ordered(tail, weight);
            neighbors[tail-1].push_ordered(head, weight);
        }
        bool is_neighbor(int head, int tail){
            return neighbors[head-1].find(tail) != NULL;
        }

        void set_graph_size(int size){
            Graph::set_graph_size(size);
            neighbors = new Linked_List[size];
        }

        float get_weight(int v1, int v2){
            return neighbors[v1-1].get(v2);
        }

        AdjacencyListGraph(bool weighted = false) : Graph(weighted){
        }
/*        ~AdjacencyListGraph(){
            if(neighbors != NULL)
                delete neighbors;
        }*/
};

#endif /* GRAPH_H */
