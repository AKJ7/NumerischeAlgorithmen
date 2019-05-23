//
// Created by hp on 5/23/19.
//

#include <iostream>


class Graph;

class Node
{
    int id;
    void* data;
    Node* next;
    Node* neighbour;
    friend Graph;

public:
    explicit Node(int ident) : id{ident}, next{}, data{}, neighbour{} {}
    int get() const { return id; }
    void set(int ident) noexcept { id = ident; }
    Node* getNeigh() const { return neighbour; }
    ~Node() = default;
};

class Graph
{
    Node* rootNode;
    Node* lastNode;

public:
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
        if (!findNode(from) or !findNode(to)) throw std::logic_error("Could not find node");
        static Node* currentNode;
    }
    void addEdge(int id1, int id2)
    {
        Node* node1;
        Node* node2;
        if (!(node1 = findNode(id1)) or !(node2 = findNode(id2))) throw std::logic_error("Could not find node");
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
           delete(a);
    }
};



int main()
{

    Graph graph(1);
    graph.addNode(6);
    graph.addNode(10);

    graph.addNode(14);
    graph.addNode(15);

    std::cout << (graph.findNode(10) ? "Found" : "Not Found") << std::endl; // Output: Found
    std::cout << (graph.findNode(11) ? "Found" : "Not Found") << std::endl; // Output: Not found

    graph.removeNode(1);

//    for (auto node : graph)
//        std::cout << node->get() << '\n';

    graph.addDirEdge(6, 14);
    graph.addDirEdge(6, 15);
    std::cout << graph.findNode(6)->getNeigh()->get() << std::endl;


    return EXIT_SUCCESS;
}

