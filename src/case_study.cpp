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

int main(){

    clock_t begin_time, end_time;
    double elapsed_time;
    Graph *g; 
    output.open("study_case_out.txt");

    string filename;
    string file_path = "src/graphs/";
    string path_string;
    vector<string> samples;
    samples.push_back("5");
    samples.push_back("10");
    samples.push_back("20");
    samples.push_back("50");
    samples.push_back("100");
    samples.push_back("200");
    samples.push_back("500");
    samples.push_back("1000");
    samples.push_back("2000");
    samples.push_back("5000");
    samples.push_back("7500");
    samples.push_back("10000");

    float path_weight;
    int v;

    for(int j = 0; j < samples.size(); j++){
        filename = file_path + "points-" + samples[j] + "-converted.txt";

        log_print("======================");
        log_print(samples[j]);
        log_print("======================");

        log_print("");

        g = new AdjacencyMatrixGraph(true);
        g->read_file(filename);
        
        begin_time = clock();
        path_weight = g->tsp(1, "void", 10800);
        end_time = clock();
        elapsed_time = double(end_time - begin_time) / CLOCKS_PER_SEC;
        log_print("Run time: " + to_string(elapsed_time));
        log_print("Total weight: " + to_string(path_weight));
        path_string = "1";
        v = g->latest_search_parent[0];
        while(v != 1){
            path_string += " " + to_string(v);
            v = g->latest_search_parent[v-1];
        }

        log_print("Path: " + path_string);
        delete g;

    }
    return 0;
}
