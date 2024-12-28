#ifndef FLOWRESULT_H
#define FLOWRESULT_H

#include <vector>
#include <utility>
#include "Graph.h"

class FlowResult {
private:
    std::vector<std::pair<int, int>> sourceFlows;  // (node, flow)
    std::vector<std::pair<int, int>> sinkFlows;    // (node, flow)
    int totalFlow;
    double executionTime;

public:
    FlowResult() : totalFlow(0), executionTime(0.0) {}
    
    void addSourceFlow(int node, int flow) {
        sourceFlows.push_back({node, flow});
    }
    
    void addSinkFlow(int node, int flow) {
        sinkFlows.push_back({node, flow});
    }
    
    void setTotalFlow(int flow) { totalFlow = flow; }
    void setExecutionTime(double time) { executionTime = time; }
    
    void print() const;
    void calculateFlows(const Graph& original, const Graph& residual, 
                       const std::vector<int>& sources, const std::vector<int>& sinks);
};

#endif // FLOWRESULT_H