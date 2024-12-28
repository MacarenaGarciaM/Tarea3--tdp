#include <iostream>
#include <chrono>
#include "Graph.h"
#include "MaxFlow.h"
#include "FileReader.h"
#include "FlowResult.h"

int main() {
    std::string filename;
    std::cout << "Enter the input file name: ";
    std::cin >> filename;

    FileReader reader;
    Graph originalGraph(0);  // Se redimensionará en readFile
    
    if (!reader.readFile(filename, originalGraph)) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    // Crear una copia para el grafo residual
    Graph residualGraph = originalGraph;
    
    // Obtener super fuente y super sumidero
    int superSource, superSink;
    residualGraph.addSuperSourceSink(reader.getSources(), reader.getSinks(), 
                                   superSource, superSink);

    // Medir tiempo y calcular flujo máximo
    auto start = std::chrono::high_resolution_clock::now();
    MaxFlow dinic(residualGraph, superSource, superSink);
    int maxFlow = dinic.maxFlow();
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calcular tiempo transcurrido
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // Preparar y mostrar resultados
    FlowResult result;
    result.calculateFlows(originalGraph, residualGraph, 
                         reader.getSources(), reader.getSinks());
    result.setTotalFlow(maxFlow);
    result.setExecutionTime(elapsed.count());
    result.print();

    return 0;
}
