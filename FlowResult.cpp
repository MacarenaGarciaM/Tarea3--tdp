#include "FlowResult.h"
#include <iostream>
#include <algorithm>

void FlowResult::print() const {
    std::cout << "Fuentes:\n";
    for (const auto& [node, flow] : sourceFlows) {
        std::cout << node << " " << flow << "\n";
    }
    
    std::cout << "\nSumideros:\n";
    for (const auto& [node, flow] : sinkFlows) {
        std::cout << node << " " << flow << "\n";
    }
    
    std::cout << "\nFlujo Total: " << totalFlow << "\n";
    std::cout << "Tiempo: " << executionTime << " [ms]\n";
}

void FlowResult::calculateFlows(const Graph& original, const Graph& residual,
                              const std::vector<int>& sources, const std::vector<int>& sinks) {
    sourceFlows.clear();
    sinkFlows.clear();
    
    // Calcular flujos para cada fuente
    for (int src : sources) {
        int flow = 0;
        for (int v : original.getAdj(src)) {
            int origCap = original.getCapacity(src, v);
            int resCap = residual.getCapacity(src, v);
            if (origCap > 0) {
                flow += (origCap - resCap);
            }
        }
        if (flow > 0) {
            sourceFlows.push_back({src, flow});
        }
    }
    
    // Calcular flujos para cada sumidero
    for (int snk : sinks) {
        int flow = 0;
        for (int u : original.getAdj(snk)) {
            int origCap = original.getCapacity(u, snk);
            int resCap = residual.getCapacity(u, snk);
            if (origCap > 0) {
                flow += (origCap - resCap);
            }
        }
        if (flow > 0) {
            sinkFlows.push_back({snk, flow});
        }
    }
    
    // Ordenar los resultados por número de nodo
    std::sort(sourceFlows.begin(), sourceFlows.end());
    std::sort(sinkFlows.begin(), sinkFlows.end());
}
