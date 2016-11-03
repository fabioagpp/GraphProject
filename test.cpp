#include <iostream>
#include "graph.h"

using namespace std;

int main(){
    /*Linked_List l;
    l.append_ordered(2);
    l.append_ordered(3);
    l.append_ordered(1);

    l.print();*/
    Graph *g = new AdjacencyListGraph;
    g->read_file("test.txt");
    g->generate_info();
    g->generate_dfs_tree(1);
    cout << "DFS" << endl;
    for(int i = 1; i <= 9; i ++){
        cout << "The parent of " << i << " is ";
        cout << g->latest_search_parent[i-1] << endl;
    }
    g->generate_bfs_tree(1);
    cout << "DFS" << endl;
    for(int i = 1; i <= 9; i ++){
        cout << "The parent of " << i << " is ";
        cout << g->latest_search_parent[i-1] << endl;
    }
    g->generate_connected_components();
    return 0;
}
