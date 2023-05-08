#include <iostream>
#include <algorithm>
#include <limits>
#include "priorityqueue.cpp"
#include "graph.cpp"
#include <utility>


void dijkstra(Graph* g, int source, int target) {

    //when accessing the d array, there has to be -1 to match the index of the graph file (there is no node 0)

    int n = g->getNumNodes();

    //create a priority queue where the element type is the node id (int) and the key is the distance, d[i] (double)
    PriorityQueue<int, double>* p = new PriorityQueue<int, double>();

    double d[n];
    //parent array not really used here but is in the pseudocode
    int parent[n];
    //fill the d array with infinity
    std::fill(d, d + n, std::numeric_limits<double>::infinity());

    parent[source] = source;
    d[source-1] = 0;

    p->insert(source, d[source]);

    while (!p->isEmpty()) {

        int u = p->deleteMin(); 

        if (u == target) {
            std::cout << "min: " << u << std::endl;
            break;
        }

        //relaxation
        for (int i = 0; i < g->Adj[u-1].size(); i++) {
            Edge v = g->Adj[u-1][i];

            if ((d[u-1] + v.weight) < d[v.target-1]) {
                d[v.target-1] = d[u-1] + v.weight;
                parent[v.target-1] = u;

                if (p->isElementOf(v.target)) {
                    p->decreaseKey(v.target, d[v.target-1]);
                }
                else {
                    p->insert(v.target, d[v.target-1]);
                }

            }


        }
    }

    std::cout <<  "distance to target: " << d[target-1] << std::endl;

}
