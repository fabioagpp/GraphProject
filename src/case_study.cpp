#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include <map>
#include "graph.h"

using namespace std;

ofstream output;

void log_print(string s){
    cout << s << endl;
    output << s << endl;
    
}

vector<int> get_path(Graph *g, int head, int tail){
    vector<int> path;
    int current = tail;
    while(current != head and current > 0){
        path.push_back(current);
        current = g->latest_search_parent[current-1];
    }
    path.push_back(current);

    return path;
}

int *get_degrees(Graph *g){
    int *degrees = new int[g->get_size()];
    fill_n(degrees, g->get_size(), 0);
    for(int i = 0; i < g->get_size(); i++){
        if(g->latest_search_parent[i] > 0){
            degrees[i]++;
            degrees[g->latest_search_parent[i]-1]++;
        }
    }
    
    return degrees;
}

vector<int> get_neighbors(Graph *g, int vertex){
    vector<int> neighbors;
    for(int i = 0; i < g->get_size(); i++){
        if(g->latest_search_parent[i] == vertex){
            neighbors.push_back(i+1);
        }
    }
    if(g->latest_search_parent[vertex-1] > 0)
        neighbors.push_back(g->latest_search_parent[vertex-1]);

    return neighbors;
}


int main(){

    clock_t begin_time, end_time;
    double elapsed_time;
    vector<int> test_vertices = {10, 20, 30, 40, 50};
    vector<float> *distances;
    vector<int> path;
    Graph *g; 
    float mst_weight;
    output.open("study_case_out.txt");

    string filename;
    string file_path = "src/graphs/";
    string path_string;
    vector<string> samples= {"grafo_1.txt", "grafo_2.txt", "grafo_3.txt",
            "grafo_4.txt", "grafo_5.txt"};

    float path_distance;

    for(int j = 0; j < 5; j++){
        filename = file_path + samples[j];

        log_print("======================");
        log_print(samples[j]);
        log_print("======================");

        log_print("");

        g = new AdjacencyListGraph(true);
        g->read_file(filename);
        distances = new vector<float>;
        
        log_print("-----------------");
        log_print("Question 1.1");
        log_print("-----------------");
        for(vector<int>::iterator vertex = test_vertices.begin();
                            vertex != test_vertices.end(); vertex++){
            begin_time = clock();
            path_distance = g->get_distance(*vertex, 1);
            path = get_path(g, *vertex, 1);
            end_time = clock();
            elapsed_time = double(end_time - begin_time) / CLOCKS_PER_SEC;
            log_print("Distance from " + to_string(*vertex) +
                        " to 1: " + to_string(path_distance));
            path_string = "Path: ";

            for(int j = 0; j < path.size(); j++){
                path_string += to_string(path[j]) + ", ";
            }

            log_print(path_string);
            log_print("Elapsed Time: " + to_string(elapsed_time) + "s");

        }
        for(int i = 0; i < test_vertices.size(); i++){
                        
        }
        delete distances;

        log_print("-----------------");
        log_print("Question 1.2");
        log_print("-----------------");
        begin_time = clock();
        mst_weight = g->mst(1, "void");
        end_time = clock();
        elapsed_time = double(end_time - begin_time) / CLOCKS_PER_SEC;
        log_print("MST Weight: " + to_string(mst_weight));
        log_print("Total Elapsed Time: " + to_string(elapsed_time) + "s");

/*
        log_print("-----------------");
        log_print("Question 1.3");
        log_print("-----------------");
        begin_time = clock();
        mst_weight = g->get_average_distance();
        end_time = clock();
        elapsed_time = double(end_time - begin_time) / CLOCKS_PER_SEC;
        log_print("Average Distance: " + to_string(mst_weight));
        log_print("Total Elapsed Time: " + to_string(elapsed_time) + "s");

        log_print("");
        log_print("");

        delete g;
*/
    }

    map<string, int> name_index;
    map<int, string> index_name;

    // Reads name id equivalence file.
    filename = file_path + "rede_colaboracao_vertices.txt";
    string line;
    string name;
    string id_str;
    int id;
    ifstream input(filename.c_str());
    while(getline(input, line)){
        stringstream line_stream(line);
        getline(line_stream, id_str, ',');
        sscanf(id_str.c_str(), "%d", &id);
        getline(line_stream, name, ',');
        name_index[name] = id;
        index_name[id] = name;
    }

    input.close();

    string root = "Edsger W. Dijkstra";
    vector<string> targets = {"Alan M. Turing", "J. B. Kruskal",
            "Jon M. Kleinberg", "Éva Tardos", "Daniel R. Figueiredo"};

    filename = file_path + "rede_colaboracao.txt";
    g = new AdjacencyListGraph(true);
    g->read_file(filename);
    g->dijkstra(name_index[root], "void");
    
    log_print("-----------------");
    log_print("Question 2.1");
    log_print("-----------------");
    log_print("Distance between " + root + " and:");
    float depth;
    float infinite = numeric_limits<float>::max();

    for(int i = 0; i < 5; i++){
        depth = g->latest_search_depth[name_index[targets[i]]-1];
        if(depth == infinite)
            log_print(targets[i] + ": Infinite");
        else
            log_print(targets[i] + ": " + to_string(depth));
    }

    path = get_path(g, name_index[root], name_index[targets[4]]);

    for(vector<int>::iterator i = path.begin(); i != path.end(); i++){
        path_string += index_name[*i] + ", ";
    }

    log_print("The path between Dijkstra and Daniel is:");
    log_print(path_string);
    log_print("");

    log_print("-----------------");
    log_print("Question 2.2a");
    log_print("-----------------");
    g->mst(2722, "void");
    int *degrees = get_degrees(g);
    int max_vertex;
    int *max_degree;
    for(int i = 0; i < 3; i++){
        max_degree = max_element(degrees, degrees+g->get_size());
        max_vertex = distance(degrees, max_degree);
        log_print(index_name[max_vertex+1] + " " + to_string(*max_degree));
        degrees[max_vertex] = 0;
    }


    output.close();

    log_print("-----------------");
    log_print("Question 2.2b");
    log_print("-----------------");
    targets = {root, targets[4]};
    vector<int> neighbors;

    for(int i = 0; i < 2; i++){
        log_print("The neighbors of " + targets[i] + " are: ");
        neighbors = get_neighbors(g, name_index[targets[i]]);
        for(int j = 0; j < neighbors.size(); j++){
            log_print(index_name[neighbors.at(j)]);
        }
        log_print("");
    }

    return 0;
}
