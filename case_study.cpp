#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include "graph.h"

using namespace std;

double time_function(Graph *g, void (Graph::*f) (int, string) , vector<int> *test_vertices){
    clock_t begin, end;
    begin = clock();
    for(vector<int>::iterator vertex = test_vertices->begin();
                        vertex != test_vertices->end(); vertex++){
        (g->* f)(*vertex, "void");
    }
    end = clock();
    return double(end - begin) / CLOCKS_PER_SEC;

}

void question_4(Graph *g, void (Graph::*f) (int, string)){
    for(int i = 1; i <= 5; i++){
        cout << "Generating tree for root " << i << "...\r\n";
        (g->* f)(i, "void");
        for(int j = 10; j <= 50; j += 10){
            cout << "The parent of " << j << " is ";
            cout << g->latest_search_parent[j-1] << "\r\n";
        }
    }
}

int main(){

    clock_t begin_time, end_time;
    int max_vertex, new_rand;
    int min_vertex = 1; 
    double elapsed_time;
    int max_degree, min_degree;
    vector<int> *test_vertices;
    Graph *g; 
    int diameter;

    string filename;
    vector<string> samples= {"as_graph.txt", "subdblp.txt", "dblp.txt"};

for(int j = 0; j < 3; j++){
    filename = samples[j];

    cout << "Testing the graph " << filename << "...\n";

    // Testing Adjacency Matrix
    g = new AdjacencyMatrixGraph;
//    g = new AdjacencyListGraph;
    cout << "Testing adjacency matrix..." << endl;
    g->read_file(filename);
    cout << "Check out the memory usage! Press any key to continue..." << endl;
    getchar();
    // Generating testing values for questions 2 and 3
    max_vertex = g->get_size();
    test_vertices = new vector<int>;
    for(int i = 0; i < 10; i++){
        new_rand = min_vertex + (rand() % (max_vertex - min_vertex + 1));
        while(find(test_vertices->begin(), test_vertices->end(), new_rand) 
                                                    != test_vertices->end()){
            new_rand = min_vertex + (rand() % (max_vertex - min_vertex + 1));
        }
        test_vertices->push_back(new_rand);
    }
    
    // Timing BFS
    elapsed_time = time_function(g, &Graph::generate_bfs_tree, test_vertices);
    cout << "BFS: "  << elapsed_time << endl;
    // Timing DFS
    elapsed_time = time_function(g, &Graph::generate_dfs_tree, test_vertices);
    cout << "DFS: " << elapsed_time << endl;
    delete g;
    // Testing Adjacency List
    g = new AdjacencyListGraph;
    cout << "Testing adjacency list..." << endl;
    g->read_file(filename);
    cout << "Check out the memory usage! Press any key to continue..." << endl;
    getchar();

    // Timing BFS
    elapsed_time = time_function(g, &Graph::generate_bfs_tree, test_vertices);
    cout << "BFS: " << elapsed_time << endl;

    // Timing DFS
    elapsed_time = time_function(g, &Graph::generate_dfs_tree, test_vertices);
    cout << "DFS: " << elapsed_time << endl;

    // Question 4
    cout << "Question 4:" << endl;
    cout << "BFS:" << endl;
    question_4(g, &Graph::generate_bfs_tree);
    cout << "DFS:" << endl;
    question_4(g, &Graph::generate_dfs_tree);


    // Question 5
    cout << "Question 5:" << endl;
    g->generate_connected_components("void");
    cout << "O grafo posui " << g->components->size();
    cout << " componente(s) conexa(s)." << endl;
    cout << "A maior componente possui tamanho " << g->components->front().size() << ".\n";
    cout << "A menor componente possui tamanho " << g->components->back().size() << ".\n";
    
    // Question 6
    cout << "Question 6:" << endl;
    max_degree = 0;
    min_degree = g->get_size();
    for(int i = 0; i < g->get_size(); i++){
        max_degree = max(g->degree[i], max_degree);
        min_degree = min(g->degree[i], min_degree);
    }
    cout << "O grau máximo deste grafo é " << max_degree << ".\n";
    cout << "O grau mínimo deste grafo é " << min_degree << ".\n";
    g->generate_info("info_" + filename);

    // Question 7
    cout << "Question 7:" << endl;
    begin_time = clock();
    diameter = g->get_diameter();
    end_time = clock();
    elapsed_time = double(end_time - begin_time) / CLOCKS_PER_SEC;

    cout << "O diametro do grafo é " << diameter << ".\n";
    cout << "O tempo para calcular o diametro foi de "<< elapsed_time << ".\n";

    delete g;
}


    return 0;
}
