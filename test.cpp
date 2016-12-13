#include <iostream>
#include <vector>
#include "src/graph.h"

using namespace std;

int main(){
    Graph *g = new AdjacencyMatrixGraph(true);
    vector<string> sizes;
    sizes.push_back("5");
    sizes.push_back("10");
    sizes.push_back("20");
    sizes.push_back("50");
    sizes.push_back("100");
    sizes.push_back("200");
    sizes.push_back("500");
/*    sizes.push_back("1000");
    sizes.push_back("2000");
    sizes.push_back("5000");
    sizes.push_back("7500");
    sizes.push_back("10000");
*/
    string filename;
    string output;
    for(int i = 0; i < sizes.size(); i++){
        filename = "src/graphs/points-" + sizes.at(i) + "-converted.txt";
        cout << filename << "...";
        g->read_file(filename);
        output = "point-" + sizes.at(i) + ".txt";
        g->tsp(1, output);
        cout << "Complete" << endl;
    }
    return 0;
}
