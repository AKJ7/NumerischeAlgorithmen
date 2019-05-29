//
// Created by hp on 5/29/19.
//

#include <iostream>
#include <vector>

class Graph;
class Edge;
class Node;

class Edge
{
    Node* neighbour;
    int8_t gerichtet;
    friend Node;
public:
    /// @param geric 0 : ungerichtet, 1: Postiv gerichtet, -1: Negativ gerichtet
    explicit Edge(Node* neigh, int8_t geric) : neighbour{neigh}, gerichtet{geric} {};
    ~Edge() = default;
};


class Node
{
    void* data;
    Node* next;
    Node* neighbour;
    std::vector<Edge*> neighbours;
    friend Graph;
protected:
    int id;
    char flavour[10];
public:
    explicit Node(int ident) : id{ident}, next{}, data{}, neighbour{}, flavour{} {}
    int get() const { return id; }
    void set(int ident) noexcept { id = ident; }
    void addVertice(Node* node, uint8_t dir) { neighbours.emplace_back(new Edge(node, dir)); }
    Node* getNeigh() const { return neighbour; }
    void printNeighbours()
    {
        for (auto& neigh: neighbours)
            std::cout << neigh->neighbour->get() << ' ';
    }
    virtual void print()
    {
        std::cout << "Id: " << id << ", Flavour: " << flavour << '\n';
    }
    ~Node()
    {
        for (auto& ver : neighbours)
            delete(ver);
    };
};


class Graph
{
    Node* rootNode;
    Node* lastNode;
public:
    explicit Graph(int i) { lastNode = new Node(i); rootNode = lastNode; };
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
    Node* findNode(int ident) noexcept
    {
        for (auto a : *this)
        {
            if (a->id == ident)
                return a;
        }
        return nullptr;
    }
    void addDirEdge(int from, int to)
    {
        Node* node1;
        Node* node2;
        if (!(node1 = findNode(from)) or !(node2 = findNode(to))) throw std::logic_error("Could not find node");
        node1->addVertice(node2, 1);
        node2->addVertice(node1, -1);
    }
    void addEdge(int id1, int id2)
    {
        Node* node1;
        Node* node2;
        if (!(node1 = findNode(id1)) or !(node2 = findNode(id2))) throw std::logic_error("Could not find node");
        node1->addVertice(node2, 0);
        node2->addVertice(node1, 0);
    }
    void removeNode(int ident)
    {
        auto found = findNode(ident);
        if (!found) throw std::logic_error("Could not find node");
        auto findPrevious = [&](int id) -> Node*
        {
            for (auto a: *this)
            {
                if (a->next->id == id)
                    return a;
            }
            return nullptr;
        };
        if (found != rootNode)
        {
            findPrevious(ident)->next = found->next;
            delete(found);
            return;
        }
        auto ptr = rootNode->next;
        delete(rootNode);
        rootNode = ptr;
    }
    void print()
    {
        for (auto node : *this)
            node->print();
    }
    void printNodes()
    {
        for (Node* node : *this)
            node->print();
    }
    class NodeIterator : std::iterator<std::input_iterator_tag, int, int, Node*, Node*>
    {
    private:
        Node* current;
    public:
        explicit NodeIterator(Node* node) : current{node} {}
        NodeIterator& operator++() { current = current->next == nullptr ? nullptr : current->next; return *this;}
        NodeIterator operator++(int) { NodeIterator toReturn  = *this; ++(*this); return toReturn;}
        bool operator==(NodeIterator rhs) const { return current == rhs.current; }
        bool operator!=(NodeIterator rhs) const {return current != rhs.current; }
        reference operator*() const { return current; }
    };
    NodeIterator begin() { return NodeIterator(rootNode); }
    NodeIterator end() { return NodeIterator(lastNode->next); }
    ~Graph()
    {
        for (auto a : *this)
        {
            if (a) delete(a);
        }
    }
};


class Node1: public Node
{
private:
    char* data;
public:
    explicit Node1(int ident, char* dat): Node(ident), data{dat} {}
    void print() override
    {
        std::cout << "Id: " << id << ", Data: " << data << '\n';
    }
    ~Node1() = default;
};


class Node2: public Node
{
private:
    double data;
public:
    Node2(int ident, double dat) : Node(ident), data{dat} {}
    void print() override
    {
        std::cout << "Id: " << id << ", Data: " << data << '\n';
    }
    ~Node2() = default;
};


class Node3: public Node
{
private:
    void* data;
    int length;
public:
    Node3(int ident, void *dat, int len) : Node(ident), data{dat}, length{len} {}
    void print() override
    {
        std::cout << "Id: " << id << ", Data: " << data << ", Length: " << length << '\n';
    }
    ~Node3() = default;
};



int main()
{
    Node* node = new Node(5);
    node->print();

    Node1* node1 = new Node1(10, const_cast<char*>("keine Ahnung"));
    node1->print();

    Node2* node2 = new Node2(20, 40.0);
    node2->print();

    Node3* node3 = new Node3(80, static_cast<void*>(const_cast<char*>("wieder keine Ahnung")), 18);
    node3->print();

    Graph graph(100);
    graph.addNode(node);
    graph.addNode(node1);
    graph.addNode(node2);
    graph.addNode(node3);

    std::cout << '\n';
    graph.printNodes();
    std::cout << '\n';
    graph.print();

    return EXIT_SUCCESS;
}