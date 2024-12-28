#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <algorithm>

bool FileReader::readFile(const std::string& filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file) return false;

    // Leer fuentes
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    int source;
    while (iss >> source) {
        sources.push_back(source);
        maxVertex = std::max(maxVertex, source);
    }

    // Leer sumideros
    std::getline(file, line);
    iss.clear();
    iss.str(line);
    int sink;
    while (iss >> sink) {
        sinks.push_back(sink);
        maxVertex = std::max(maxVertex, sink);
    }

    // Leer aristas
    int u, v, cap;
    while (file >> u >> v >> cap) {
        maxVertex = std::max(maxVertex, std::max(u, v));
    }
    
    // Reiniciar el archivo para leer las aristas de nuevo
    file.clear();
    file.seekg(0);
    std::getline(file, line); // Saltar línea de fuentes
    std::getline(file, line); // Saltar línea de sumideros

    // Crear el grafo con el tamaño correcto
    graph = Graph(maxVertex + 1);
    
    // Agregar las aristas
    while (file >> u >> v >> cap) {
        graph.addEdge(u, v, cap);
    }

    return true;
}