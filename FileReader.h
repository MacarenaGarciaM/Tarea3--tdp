#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <string>
#include "Graph.h"

class FileReader {
private:
    std::vector<int> sources;
    std::vector<int> sinks;
    int maxVertex;

public:
    FileReader() : maxVertex(-1) {}
    
    bool readFile(const std::string& filename, Graph& graph);
    const std::vector<int>& getSources() const { return sources; }
    const std::vector<int>& getSinks() const { return sinks; }
    int getMaxVertex() const { return maxVertex; }
};

#endif // FILEREADER_H
