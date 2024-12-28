#ifndef MAXFLOW_H
#define MAXFLOW_H

#include "Graph.h"
#include "State.h"

class MaxFlow {
private:
    Graph& graph;
    State state;
    int source;
    int sink;
    bool bfs();
    int dfs(int u, int flow);

public:
    MaxFlow(Graph& g, int s, int t);
    int maxFlow();
};

#endif // MAXFLOW_H
