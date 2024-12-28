#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;

public:
    Graph(int n);
    void addEdge(int u, int v, int cap);
    int getCapacity(int u, int v) const;
    const vector<int>& getAdj(int u) const;
    void updateCapacity(int u, int v, int flow);
    int size() const;
    void addSuperSourceSink(const vector<int>& sources, const vector<int>& sinks, int& superSource, int& superSink);
};

#endif // GRAPH_H
