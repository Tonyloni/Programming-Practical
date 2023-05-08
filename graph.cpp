#include <iostream>
#include <list> 
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct Node {
    double coordinate_x;
    double coordinate_y;

    public:

    Node() {
        coordinate_x = 0;
        coordinate_y = 0;
    }

    void setCoords(double x, double y) {
        this->coordinate_x = x;
        this->coordinate_y = y;
    }
};

struct Edge {
    int target;
    double weight;

    Edge() {
        weight = INFINITY;
    }

    Edge(int target) {
        weight = INFINITY;
        this->target = target;
    }
};

class Graph {
    //its all public ik, it was easier, but should be changed to private of course
    public:
    int numNodes;
    int numEdges;
    vector<Edge>* Adj; //Array of adjacencies
    vector<Node> Nodes; //Node Array for coordinates
 
    Graph(int n, int m) : Nodes(n) {
        Adj = new vector<Edge> [n];
        this->numNodes = n;
        this->numEdges = m;
    }

    Graph() {}

    int getNumNodes() {
        return this->numNodes;
    }

    void addEdge(int sourcenode, int targetnode) {

        //create new edge, calculate weight and add it to the adjacencie array
        Edge e = Edge(targetnode);

        //euclidian norm? idk dude, but should be
        e.weight = sqrt(    pow(Nodes[targetnode-1].coordinate_x - Nodes[sourcenode].coordinate_x, 2.0)
                        +   pow(Nodes[targetnode-1].coordinate_y - Nodes[sourcenode].coordinate_y, 2.0));

        Adj[sourcenode].push_back(e);
    }

    void addCoords(int node, long double x, long double y) {
        Nodes[node].setCoords(x, y);
    }

    void printGraph() {
        for (int i = 0; i < numNodes; i++) {
            cout << i+1 << " -> ";
            for (int j = 0; j < Adj[i].size(); j++) {
                cout << Adj[i][j].target << " /w:" << Adj[i][j].weight << " ";
            }
            cout << ", ";
            cout << Nodes[i].coordinate_x << "/" << Nodes[i].coordinate_y;
            cout << endl;
        }
    }

};

void readCoordinates(string filename, Graph* g) {

    //read coordinate file and add the coordinates to the Node array of the graph

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "error: file not open" << endl;
    }

    string line;

    int i = 0;

    while (getline(file, line)) {

        if (line[0] == '%') {
            continue;
        }

        stringstream ss(line);

        long double coord_x;
        long double coord_y;

        ss >> coord_x;
        ss >> coord_y;

        g->addCoords(i, coord_x, coord_y);

        i++;
    }

    file.close();

}

Graph* readGraph(string filename_graph, string filename_coords) {

    int nodes;
    int edges;
    
    ifstream file(filename_graph);

    if (!file.is_open()) {
        cout << "error: file not open" << endl;
    }

    //read first line of the graph file to initialize the graph with nodes and edges
    string line;

    getline(file, line);

    while (line[0] == '%') {
        getline(file, line);
    }

    stringstream ss(line);
    ss >> nodes;
    ss >> edges;

    //initialize graph
    Graph* g = new Graph(nodes, edges);

    //read coordinate file and initialize coordinates of the nodes in the graph
    readCoordinates(filename_coords, g);

    int i = 0;

    //read adjacencies of the nodes in the graph file
    while (getline(file, line)) {

        if (line[0] == '%') {
            continue;
        }

        stringstream ss(line);

        int target;

        while ( ss >> target) {
            g->addEdge(i, target);
        }

        i++;
    }

    file.close();

    //g.printGraph();

    return g;

}



