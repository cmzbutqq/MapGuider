#pragma once
#include <cmath>
#include <vector>

struct Vec2 {
    double x, y;
    Vec2(){}
    Vec2(double x, double y) : x(x), y(y) {}
    Vec2 operator-(const Vec2 &v) const { return Vec2(x - v.x, y - v.y); }
    double length() const { return std::sqrt(x * x + y * y); }
    double dist(const Vec2 &v) const { return (*this - v).length(); }
};

class Graph;

struct Edge {
    int beg, end;    // vertices
    double capacity; // capacity
    double flow;     // current flow
    double length;   // road length
    double cost;     // travel time,which is cLf(n/v)
    Graph &graph;    // the graph it belongs to
    void updateTime();

    /**
     * @brief Construct a new Edge object
     * @warning this constructor will not add itself to the graph
     */
    
    Edge(int beg, int end, double capacity, Graph &graph); // constructor
};

using adjList = std::vector<std::vector<Edge>>; // adjacency list
class Graph {
  private:
    int V;
    int E;
    std::vector<Vec2> vertices;
    adjList edges;

  public:
    Graph(std::vector<Vec2> verts);
    void addEdge(int start, int end, double capacity);
    std::vector<Vec2> getVertices() const;
    adjList getEdges() const;
    void printGraph();
};
/**
 * @brief
 *
 * @param V vertice count
 * @param stddev stddev of the normal distribution
 * @param E desired edge count
 * @return Graph
 *
 * @warning this function will not check if the graph is connected
 */
Graph randomGraph(int V, double stddev, double E);