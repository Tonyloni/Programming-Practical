#include <iostream>
#include "argtable3.h"
#include <fstream>
#include "dijkstra.cpp"
#include <chrono>

int main(int argc, char* argv[]) {

    //start clock for duration of the algorithm
    auto start_time = std::chrono::high_resolution_clock::now();

    int source_node = -1;
    int target_node = -1;
    const char* graph_filename = NULL;
    const char* coordinates_filename = NULL;

    // Define the argument structures
    struct arg_int* arg_source = arg_int0("s", "source", "<s>", "Source node");
    struct arg_int* arg_target = arg_int0("t", "target", "<t>", "Target node");
    struct arg_str* arg_graph = arg_str0("g", "graph", "<file>", "Graph filename");
    struct arg_str* arg_coordinates = arg_str0("c", "coordinates", "<file>", "Coordinates filename");
    struct arg_end* end = arg_end(20);

    // Create an array of pointers to the argument structures
    void* argtable[] = { arg_source, arg_target, arg_graph, arg_coordinates, end };

    // Parse the command-line arguments
    int nerrors = arg_parse(argc, argv, argtable);

    // Check for parsing errors
    if (nerrors > 0) {
        arg_print_errors(stderr, end, "my_program");
        arg_print_syntax(stderr, argtable, "\n");
        arg_print_glossary(stderr, argtable, "  %-25s %s\n");
        arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
        exit(1);
    }

    // Get the values of the parsed arguments
    source_node = arg_source->count > 0 ? arg_source->ival[0] : -1;
    target_node = arg_target->count > 0 ? arg_target->ival[0] : -1;
    graph_filename = arg_graph->count > 0 ? arg_graph->sval[0] : NULL;
    coordinates_filename = arg_coordinates->count > 0 ? arg_coordinates->sval[0] : NULL;

    // Free the memory allocated by Argtable
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

    // Check if all required arguments are provided
    if (source_node == -1 || target_node == -1 || graph_filename == NULL || coordinates_filename == NULL) {
        printf("Error: Missing required arguments\n");
        exit(1);
    }

    printf("Source node: %d\n", source_node);
    printf("Target node: %d\n", target_node);
    printf("Graph filename: %s\n", graph_filename);
    printf("Coordinates filename: %s\n", coordinates_filename);

    Graph *g = new Graph();
    g = readGraph(graph_filename, coordinates_filename);
    dijkstra(g, source_node, target_node);

    //stop clock
    auto end_time = std::chrono::high_resolution_clock::now();

    //calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Time taken: " << duration << " milliseconds" << std::endl;


    return 0;
}
