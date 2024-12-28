#include "Graph.h"

Graph::Graph(int n) : vertices(n), capacity(n, vector<int>(n, 0)), adj(n) {}

void Graph::addEdge(int u, int v, int cap) {
    capacity[u][v] += cap;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int Graph::getCapacity(int u, int v) const {
    return capacity[u][v];
}

const vector<int>& Graph::getAdj(int u) const {
    return adj[u];
}

void Graph::updateCapacity(int u, int v, int flow) {
    capacity[u][v] -= flow;
    capacity[v][u] += flow;
}

int Graph::size() const {
    return vertices;
}

void Graph::addSuperSourceSink(const vector<int>& sources, const vector<int>& sinks, int& superSource, int& superSink) {
    superSource = vertices++;
    superSink = vertices++;

    capacity.resize(vertices, vector<int>(vertices, 0));
    adj.resize(vertices);

    // Conecta superfuente a cada fuente original
    for (int src : sources) {
        int totalCap = 0;
        for (int v : adj[src]) {
            totalCap += capacity[src][v];
        }
        if (totalCap > 0) {  // Evita agregar conexiones sin capacidad
            addEdge(superSource, src, totalCap);
        }
    }

    // Conecta cada sumidero original al supersumidero
    for (int snk : sinks) {
        int totalCap = 0;
        for (int u : adj[snk]) {
            totalCap += capacity[u][snk];
        }
        if (totalCap > 0) {  // Evita agregar conexiones sin capacidad
            addEdge(snk, superSink, totalCap);
        }
    }
}
