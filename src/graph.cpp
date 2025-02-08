#include "Graph.h"
#include <ctime>
#include <iostream>

Edge::Edge(int beg, int end, double capacity, Graph &graph)
    : beg(beg), end(end), capacity(capacity), flow(0.0), graph(graph) {
    Vec2 &v1 = graph.getVertices()[beg];
    Vec2 &v2 = graph.getVertices()[end];
    length = v1.dist(v2);
    updateTime();
}

void Edge::updateTime() {
    double THRESHOLD = 0.5;
    double C = 2;
    double e = 2.718281828459045;
    if (flow / capacity <= THRESHOLD)
        cost = C * length;
    else
        cost = C * length * (1 + e * (flow / capacity));
}
Graph::Graph(std::vector<Vec2> verts) {
    V = verts.size();
    E = 0;
    vertices = verts;
    edges = adjList(V);
    for (int i = 0; i < V; i++) {
        edges[i] = std::vector<Edge>();
    }
}

void Graph::addEdge(int start, int end, double capacity) {
    edges[start].push_back(Edge(start, end, capacity, *this));
    E++;
}

std::vector<Vec2> Graph::getVertices() const { return vertices; }
adjList Graph::getEdges() const { return edges; }

void Graph::printGraph() {
    for (int i = 0; i < V; i++) {
        std::cout << "Vertex " << i << " is at " << vertices[i].x
                  << vertices[i].y << std::endl;
    }
    for (int i = 0; i < V; i++) {
        std::cout << "Vertex " << i << " has edges: ";
        for (Edge e : edges[i]) {
            std::cout << " -> " << e.end << " dist: " << e.length
                      << " cap: " << e.capacity << " flow: " << e.flow
                      << " cost: " << e.cost << std::endl;
        }
    }
}
#include <random>
Graph randomGraph(int V, double stddev, double E) {
    std::random_device rd;
    std::mt19937 gen(rd());
    double mean = 0.0;
    std::normal_distribution<> dist(mean, stddev);
    // random vertices
    auto v = std::vector<Vec2>(V);
    for (int i = 0; i < V; i++) {
        double x = dist(gen), y = dist(gen);
        v[i] = Vec2(x, y);
    }
    auto g = Graph(v);
    // random edges
    for (int i = 0; i < E; i++) {
        int start = rand() % V, end = rand() % V;
        while (end == start)
            start = rand() % V, end = rand() % V;
        double capacity = dist(gen);
        g.addEdge(start, end, capacity);
    }
    return g;
}
int main() {
    Graph g = randomGraph(10, 1, 10);
    g.printGraph();
}