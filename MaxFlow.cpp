#include "MaxFlow.h"
#include <queue>
#include <limits>

MaxFlow::MaxFlow(Graph& g, int s, int t) : graph(g), state(g.size()), source(s), sink(t) {}

bool MaxFlow::bfs() {
    state.resetLevels();
    queue<int> q;
    q.push(source);
    state.setLevel(source, 0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph.getAdj(u)) {
            // Solo visitamos nodos no explorados con capacidad positiva
            if (state.getLevel(v) == -1 && graph.getCapacity(u, v) > 0) {
                state.setLevel(v, state.getLevel(u) + 1);
                q.push(v);
            }
        }
    }
    return state.getLevel(sink) != -1;  // Existe un camino si el nivel del sumidero no es -1
}


int MaxFlow::dfs(int u, int flow) {
    if (u == sink) {
        return flow;
    }

    for (; state.getPointer(u) < graph.getAdj(u).size(); state.incrementPointer(u)) {
        int v = graph.getAdj(u)[state.getPointer(u)];
        int availableCapacity = graph.getCapacity(u, v);

        if (state.getLevel(v) == state.getLevel(u) + 1 && availableCapacity > 0) {
            int pushed = dfs(v, min(flow, availableCapacity));
            if (pushed > 0) {
                graph.updateCapacity(u, v, pushed);
                return pushed;
            }
        }
    }
    return 0;
}

int MaxFlow::maxFlow() {
    int totalFlow = 0;

    while (bfs()) {
        state.resetPointers();
        while (int flow = dfs(source, numeric_limits<int>::max())) {
            totalFlow += flow;
        }
    }
    return totalFlow;
}
