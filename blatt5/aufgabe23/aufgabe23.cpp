//
// Created by hp on 09.05.19.
//

#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <iterator>


class Graph;

class Node
{
public:

    int id;
    void* data;
    Node* next;
    Node* neighbour;
    friend Graph;

    explicit Node(int ident) : id{ident}, next{}, neighbour{}, data{} {}
    int get() const { return id; }
    void set(int ident) noexcept { id = ident; }
};

class Graph
{
public:

    Node* rootNode;
    Node* lastNode;

    explicit Graph(int i) : lastNode{} { lastNode = new Node(i); rootNode = lastNode; };
    void addNode(int ident)
    {
        lastNode->next = new Node(ident);
        lastNode = lastNode->next;
    }
    void addNode(Node* n)
    {
        lastNode->next = n;
        lastNode = lastNode->next;
    }

    class NodeIterator : std::iterator<std::input_iterator_tag, int, int, Node*, int>
    {
    private:
        Node* current;
    public:
        explicit NodeIterator(Node* node) : current{node} {}
        NodeIterator& operator++() { current = current->next == nullptr ? nullptr : current->next; return *this;}
        NodeIterator operator++(int) { NodeIterator toReturn  = *this; ++(*this); return toReturn;}
        bool operator==(NodeIterator rhs) const { return current == rhs.current; }
        bool operator!=(NodeIterator rhs) const {return current != rhs.current; }
        reference operator* ()const { return current->id; }
    };
    NodeIterator begin() { return NodeIterator(rootNode); }
    NodeIterator end() { return NodeIterator(lastNode->next); }
    ~Graph() = default;
};




class MGraph;

class MNode
{
    int id;
    void* data;
    std::vector<MNode*> neighbours;
    friend MGraph;

public:
    explicit MNode(int ident) : id{ident}, data{} {}
    bool isBenachbart(MNode* mNode) {
        return std::find(neighbours.begin(), neighbours.end(), mNode) != neighbours.end();
    }
    void neueKante(MNode* nachbar)
    {
        neighbours.emplace_back(nachbar);
    }
    void wegKante(MNode* nachbar)
    {
        static decltype(neighbours.begin()) f;
        f = std::find(neighbours.begin(), neighbours.end(), nachbar);
        if (f == neighbours.end()) return;
        neighbours.erase(f);
    }
};


class MGraph {
    std::unordered_map<int, MNode *> edgeMap;

public:
    MGraph() = default;

    void addEdge(int id)
    {
        if (!inGraph(id))
            edgeMap[id] = new MNode(id);
    }
    void addNode(int id, int neigh) {
        if (!inGraph(id)) {
            edgeMap[id] = new MNode(id);
        }
        if (!inGraph(neigh)) {
            edgeMap[neigh] = new MNode(neigh);
        }
        edgeMap[id]->neueKante(edgeMap[neigh]);
        edgeMap[neigh]->neueKante(edgeMap[id]);
    }

    void removeNode(int id, int neigh) {
        if (!inGraph(id) || !inGraph(neigh)) return;
        edgeMap[id]->wegKante(edgeMap[neigh]);
        edgeMap[neigh]->wegKante(edgeMap[id]);
    }

    bool inGraph(int id) const {
        return edgeMap.find(id) != edgeMap.end();
    }
};


int main()
{

    Graph graph(1);
    graph.addNode(2);
    graph.addNode(7);
    graph.addNode(4);
    graph.addNode(5);

    Node myNode(11);
    graph.addNode(&myNode);

    for (int nodeId : graph)
    {
        std::cout << nodeId << '\n';
    }

    return EXIT_SUCCESS;
}