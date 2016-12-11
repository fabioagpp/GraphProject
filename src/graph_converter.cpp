#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;
typedef pair<int, int> coord;

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

float calculate_distance(coord c1, coord c2){
    float return_value;
    long int first = c1.first - c2.first;
    long int second = c1.second - c2.second;
    
    first = first*first;
    second = second*second;

    return_value = (float)first + (float)second;
    return_value = sqrt(return_value);

    return return_value;
}

void convert_graph(string filename){
    cout << "Converting graph " << filename << "...";
    ifstream input(filename.c_str());
    replace(filename, ".txt", "-converted.txt");
    ofstream output(filename.c_str());
    
    string line;
    string s1;
    string s2;
    int graph_size;
    int i1;
    int i2;
    vector<coord> points;
    
    getline(input, line);
    output << line << endl;
    sscanf(line.c_str(), "%d", &graph_size);
   
    while(getline(input, line)){
        stringstream line_stream(line);
        getline(line_stream, s1, ' ');
        sscanf(s1.c_str(), "%d", &i1);
        getline(line_stream, s2, ' ');
        sscanf(s2.c_str(), "%d", &i2);

        points.push_back(coord(i1, i2));
    }

    for(int i = 0; i < graph_size; i++){
        for(int j = i + 1; j < graph_size; j++){
            output << i + 1 << " " << j + 1 << " ";
            output << calculate_distance(points.at(i), points.at(j)) << endl;
        }
    }

    cout << " Completed" << endl;
}

int main(int argc, char* argv[]){
    convert_graph(argv[1]);
    return 0;
}
